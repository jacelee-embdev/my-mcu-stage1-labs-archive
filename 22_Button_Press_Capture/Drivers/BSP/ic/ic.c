#include "ic.h"
#include "stdio.h"
#include "string.h"

// 捕获状态标志位
struct
{
    uint8_t succed_flag;   // 捕获完成标志
    uint8_t rising_flag;   // 上升沿标志
    uint8_t falling_flag;  // 下降沿标志
    uint16_t timout_cnt;   // 超时计数
}capture_status = {0};

TIM_HandleTypeDef ic_handle = {0};

// 输入捕获初始化
void ic_init(uint16_t arr,uint16_t psc)
{
    TIM_IC_InitTypeDef ic_Config;
    
    // 1. 定时器基础配置
    ic_handle.Instance = TIM2;
    ic_handle.Init.Prescaler = psc;
    ic_handle.Init.Period = arr;
    ic_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    HAL_TIM_IC_Init(&ic_handle);
    
    // 2. 通道配置：默认检测下降沿
    ic_Config.ICPolarity = TIM_ICPOLARITY_FALLING;
    ic_Config.ICSelection = TIM_ICSELECTION_DIRECTTI; // 映射 TI2 -> IC2
    ic_Config.ICPrescaler = TIM_ICPSC_DIV1;           // 不分频
    ic_Config.ICFilter = 0;
    HAL_TIM_IC_ConfigChannel(&ic_handle,&ic_Config,TIM_CHANNEL_2);

    // 3. 开启更新中断和捕获中断
    __HAL_TIM_ENABLE_IT(&ic_handle,TIM_IT_UPDATE);
    HAL_TIM_IC_Start_IT(&ic_handle,TIM_CHANNEL_2);
}

// 硬件底层配置 (MSP)
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM2)
    {
        GPIO_InitTypeDef gpio_initstruct; 

        // 开启外设时钟
        __HAL_RCC_TIM2_CLK_ENABLE(); 
        __HAL_RCC_GPIOA_CLK_ENABLE(); 
        
        // 配置 PA1 为输入模式 (TIM2_CH2)
        gpio_initstruct.Pin=GPIO_PIN_1; 
        gpio_initstruct.Mode=GPIO_MODE_INPUT; 
        gpio_initstruct.Pull=GPIO_PULLUP; 
        gpio_initstruct.Speed=GPIO_SPEED_FREQ_HIGH; 
        HAL_GPIO_Init(GPIOA,&gpio_initstruct); 
        
        // 配置中断优先级并使能
        HAL_NVIC_SetPriority(TIM2_IRQn,2,2);
        HAL_NVIC_EnableIRQ(TIM2_IRQn);
    }
}

// TIM2 中断入口
void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&ic_handle);
}

// 捕获中断回调：核心状态机逻辑
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM2)
    {
        if(capture_status.succed_flag == 0)
        {
            // 情况2：已捕获下降沿，现在捕获到上升沿 (脉冲结束)
            if(capture_status.falling_flag == 1)
            {
                printf("UP");
                capture_status.succed_flag = 1; // 标记捕获完成

                // 切换极性检测下降沿，准备下一次
                TIM_RESET_CAPTUREPOLARITY(&ic_handle,TIM_CHANNEL_2);
                TIM_SET_CAPTUREPOLARITY(&ic_handle,TIM_CHANNEL_2,TIM_ICPOLARITY_FALLING);
                
                // 【注意】此处立即清零了状态，外部可能无法读取到 succed_flag
                memset (&capture_status,0,sizeof(capture_status));
            }
            // 情况1：捕获到下降沿 (脉冲开始)
            else
            {
                printf("DOWN");
                memset (&capture_status,0,sizeof(capture_status)); // 清空旧状态

                capture_status.falling_flag = 1; // 标记开始

                // 切换极性检测上升沿，等待结束
                TIM_RESET_CAPTUREPOLARITY(&ic_handle,TIM_CHANNEL_2);
                TIM_SET_CAPTUREPOLARITY(&ic_handle,TIM_CHANNEL_2,TIM_ICPOLARITY_RISING);
            }
        }
    }
}