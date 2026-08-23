#include "counter.h"
#include "sys.h"
#include "stdio.h"

TIM_HandleTypeDef counter_handle = {0}; // 定时器句柄

// 用于记录计数值的变量
uint16_t new_count = 0;
uint16_t old_count = 0;

/**
 * @brief  初始化定时器为外部时钟计数模式 (Slave Mode: External Clock Mode 1)
 * @param  arr: 自动重装载值 (Auto Reload Register)，通常设为 0xFFFF 以防止溢出
 * @param  psc: 预分频系数 (Prescaler)，通常设为 0 表示不分频
 * @note   使用 TIM2 的通道2 (PA1) 作为外部时钟输入源
 */
void counter_init(uint16_t arr, uint16_t psc)
{
    TIM_SlaveConfigTypeDef slave_config = {0};
    
    // 1. 基本定时器参数配置
    counter_handle.Instance = TIM2;                          // 选择定时器2
    counter_handle.Init.Prescaler = psc;                     // 预分频系数
    counter_handle.Init.Period = arr;                        // 自动重装载值
    counter_handle.Init.CounterMode = TIM_COUNTERMODE_UP;    // 向上计数模式
    counter_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    
    // 初始化定时器输入捕获时基 (虽然主要用作计数，但需初始化相关通道)
    HAL_TIM_IC_Init(&counter_handle);
    
    // 2. 从模式配置 (关键步骤)
    slave_config.SlaveMode = TIM_SLAVEMODE_EXTERNAL1;        // 设置为外部时钟模式1
    slave_config.InputTrigger = TIM_TS_TI2FP2;               // 选择输入触发源：TI2FP2 (即定时器通道2经过滤波后的信号)
    slave_config.TriggerPolarity = TIM_TRIGGERPOLARITY_FALLING; // 设置触发极性：下降沿计数
    slave_config.TriggerFilter = 0;                          // 输入滤波器：0 (不滤波)
    
    // 应用从模式配置
    HAL_TIM_SlaveConfigSynchro(&counter_handle, &slave_config);
    
    // 3. 启动定时器 (以输入捕获模式启动通道2)
    HAL_TIM_IC_Start(&counter_handle, TIM_CHANNEL_2);
}

/**
 * @brief  定时器底层硬件初始化回调函数
 * @param  htim: 定时器句柄
 * @note   此函数会被 HAL_TIM_IC_Init 调用，用于配置时钟和 GPIO
 */
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM2)
    {
        GPIO_InitTypeDef gpio_initstruct; 

        // 1. 使能外设时钟
        __HAL_RCC_TIM2_CLK_ENABLE();   // 使能 TIM2 时钟
        __HAL_RCC_GPIOA_CLK_ENABLE();  // 使能 GPIOA 时钟 (因为 TIM2_CH2 对应 PA1)
        
        // 2. 配置 GPIO 引脚 (PA1 -> TIM2_CH2)
        gpio_initstruct.Pin = GPIO_PIN_1;           // 选择 PA1
        gpio_initstruct.Mode = GPIO_MODE_AF_PP;     // 复用推挽模式 (作为输入使用复用功能)
        gpio_initstruct.Pull = GPIO_PULLUP;         // 上拉 (保证空闲时为高电平，配合下降沿触发)
        gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH; // 高速
        HAL_GPIO_Init(GPIOA, &gpio_initstruct); 
    }
}

/**
 * @brief  获取并打印当前的计数值
 * @note   轮询方式检测计数器变化
 */
void get_count(void)
{
    // 读取 TIM2 的计数器寄存器 (CNT)
    new_count = __HAL_TIM_GET_COUNTER(&counter_handle);
    
    // 如果计数值发生变化
    if(new_count != old_count)
    {
        old_count = new_count;      // 更新旧值
        printf("CNT:%d\r\n", new_count); // 打印当前脉冲计数值
    }
}