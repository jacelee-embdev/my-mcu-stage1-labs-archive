#include "ic.h"
#include "stdio.h"
#include "string.h"

// 定义捕获状态结构体
struct
{
    uint8_t succeed_flag;   // 捕获成功标志 (1: 完成一次完整脉冲捕获)
    uint8_t rising_flag;    // 上升沿标志 (暂未使用，可扩展)
    uint8_t falling_flag;   // 下降沿/开始捕获标志 (1: 已捕获到下降沿，正在计时)
    uint16_t timout_cnt;    // 定时器溢出计数 (处理长脉冲)
} capture_status = {0};

uint16_t last_cnt = 0;      // 存储捕获寄存器(CCR)的值

TIM_HandleTypeDef ic_handle = {0};

/**
  * @brief  输入捕获初始化函数
  * @param  arr: 自动重装载值
  * @param  psc: 预分频系数
  */
void ic_init(uint16_t arr, uint16_t psc)
{
    TIM_IC_InitTypeDef ic_config = {0};
    
    // 1. 配置定时器基础参数
    ic_handle.Instance = TIM2;
    ic_handle.Init.Prescaler = psc;
    ic_handle.Init.Period = arr;
    ic_handle.Init.CounterMode = TIM_COUNTERMODE_UP; // 向上计数
    HAL_TIM_IC_Init(&ic_handle);
    
    // 2. 配置输入捕获通道参数
    // 初始配置为捕获下降沿 (检测按键按下动作)
    ic_config.ICPolarity = TIM_ICPOLARITY_FALLING;
    ic_config.ICSelection = TIM_ICSELECTION_DIRECTTI; // 映射 TI2 输入到 IC2
    ic_config.ICPrescaler = TIM_ICPSC_DIV1;           // 输入不分频
    ic_config.ICFilter = 0;                           // 不使用滤波器
    HAL_TIM_IC_ConfigChannel(&ic_handle, &ic_config, TIM_CHANNEL_2);

    // 3. 开启中断
    // 开启更新中断 (处理计数溢出) 和 捕获中断 (处理边沿检测)
    __HAL_TIM_ENABLE_IT(&ic_handle, TIM_IT_UPDATE);
    HAL_TIM_IC_Start_IT(&ic_handle, TIM_CHANNEL_2);
}

/**
  * @brief  定时器底层硬件配置 (MSP回调)
  * 负责时钟使能、GPIO配置、NVIC配置
  */
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM2)
    {
        GPIO_InitTypeDef gpio_initstruct; 

        // 1. 使能外设时钟
        __HAL_RCC_TIM2_CLK_ENABLE(); 
        __HAL_RCC_GPIOA_CLK_ENABLE(); 
        
        // 2. 配置 GPIO PA1 (对应 TIM2_CH2)
        gpio_initstruct.Pin = GPIO_PIN_1; 
        gpio_initstruct.Mode = GPIO_MODE_INPUT; 
        gpio_initstruct.Pull = GPIO_PULLUP;       // 上拉电阻 (默认高电平，按下为低)
        gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH; 
        HAL_GPIO_Init(GPIOA, &gpio_initstruct); 
        
        // 3. 配置 NVIC 中断优先级
        HAL_NVIC_SetPriority(TIM2_IRQn, 2, 2);
        HAL_NVIC_EnableIRQ(TIM2_IRQn);
    }
}

/**
  * @brief  TIM2 中断服务函数
  */
void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&ic_handle);
}

/**
  * @brief  输入捕获中断回调函数 (核心逻辑)
  * 实现状态机：下降沿开始计时 -> 上升沿停止计时
  */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM2)
    {
        // 仅在未完成一次完整捕获时处理
        if(capture_status.succeed_flag == 0)
        {
            // --- 阶段2：检测到上升沿 (脉冲结束) ---
            if(capture_status.falling_flag == 1)
            {
                printf("UP\n"); // 调试信息：检测到松开
                
                capture_status.succeed_flag = 1; // 标记本次捕获成功
                
                // 读取当前捕获值 (即脉冲结束时的计数值)
                last_cnt = HAL_TIM_ReadCapturedValue(&ic_handle, TIM_CHANNEL_2);

                // 恢复设置：切换极性为检测下降沿，为下一次捕获做准备
                TIM_RESET_CAPTUREPOLARITY(&ic_handle, TIM_CHANNEL_2);
                TIM_SET_CAPTUREPOLARITY(&ic_handle, TIM_CHANNEL_2, TIM_ICPOLARITY_FALLING);
            }
            // --- 阶段1：检测到下降沿 (脉冲开始) ---
            else
            {
                printf("DOWN\n"); // 调试信息：检测到按下
                
                // 清空状态结构体，准备新一轮测量
                memset(&capture_status, 0, sizeof(capture_status));

                capture_status.falling_flag = 1; // 标记已开始
                
                // 核心操作：清零计数器，从0开始计数，简化后续计算
                __HAL_TIM_DISABLE(&ic_handle);
                __HAL_TIM_SET_COUNTER(&ic_handle, 0);

                // 切换极性：改为检测上升沿 (等待按键松开)
                TIM_RESET_CAPTUREPOLARITY(&ic_handle, TIM_CHANNEL_2);
                TIM_SET_CAPTUREPOLARITY(&ic_handle, TIM_CHANNEL_2, TIM_ICPOLARITY_RISING);
                
                __HAL_TIM_ENABLE(&ic_handle);
            }
        }
    }
}

/**
  * @brief  定时器更新中断回调 (处理溢出)
  * 当脉冲时间超过定时器最大量程 (如65535) 时调用
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM2)
    {
        // 如果正在捕获过程中 (已开始但未结束)
        if(capture_status.succeed_flag == 0)
        {
            if(capture_status.falling_flag == 1)
            {
                capture_status.timout_cnt++; // 记录溢出次数
            }
        }
    }
}

/**
  * @brief  主循环调用函数：计算并打印脉冲时长
  */
void get_pressed_time(void)
{
    // 如果捕获成功标志被置位
    if(capture_status.succeed_flag == 1)
    {
        // 计算总时间 = (溢出次数 * 计数周期) + 剩余计数值
        // 假设定时器是16位的 (65536)
        printf("Time: %d us\n", capture_status.timout_cnt * 65536 + last_cnt);
        
        // 处理完毕，清空状态，允许下一次捕获
        memset(&capture_status, 0, sizeof(capture_status));
    }
}