#include "ic.h"
#include "stdio.h"

TIM_HandleTypeDef ic_handle = {0};

/**
  * @brief  TIM2输入捕获初始化
  * @param  arr: 自动重装值
  * @param  psc: 预分频器值
  * @retval 无
  */
void ic_init(uint16_t arr,uint16_t psc)
{
    TIM_IC_InitTypeDef ic_Config;
    
    // 配置TIM2基本参数：向上计数模式
    ic_handle.Instance = TIM2;
    ic_handle.Init.Prescaler = psc;
    ic_handle.Init.Period = arr;
    ic_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    HAL_TIM_IC_Init(&ic_handle);        // 初始化输入捕获（会调用底层硬件初始化函数）
    
    // 配置通道2捕获参数：下降沿、直连输入、不分频、无滤波
    ic_Config.ICPolarity = TIM_ICPOLARITY_FALLING;
    ic_Config.ICSelection = TIM_ICSELECTION_DIRECTTI;   // 直连输入（TI2直接映射到通道2）
    ic_Config.ICPrescaler = TIM_ICPSC_DIV1;             // 捕获不分频（每个下降沿都捕获）
    ic_Config.ICFilter = 0;                             // 无输入滤波（直接检测电平变化）
    HAL_TIM_IC_ConfigChannel(&ic_handle,&ic_Config,TIM_CHANNEL_2);

    __HAL_TIM_ENABLE_IT(&ic_handle,TIM_IT_UPDATE);      // 开启定时器更新中断（溢出中断）
    HAL_TIM_IC_Start_IT(&ic_handle,TIM_CHANNEL_2);      // 启动通道2的捕获中断（触发后进入回调）
}

/**
  * @brief  TIM2输入捕获底层硬件初始化（HAL自动调用）
  * @param  htim: 定时器句柄
  * @retval 无
  */
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM2)
    {
        GPIO_InitTypeDef gpio_initstruct; 

        // 使能时钟
        __HAL_RCC_TIM2_CLK_ENABLE(); 
        __HAL_RCC_GPIOA_CLK_ENABLE();       // 开启GPIOA时钟（TIM2_CH2映射到GPIOA_PIN_1）
        
        // 初始化PA1引脚
        gpio_initstruct.Pin=GPIO_PIN_1; 
        gpio_initstruct.Mode=GPIO_MODE_INPUT;   // 输入模式（捕获外部电平）
        gpio_initstruct.Pull=GPIO_PULLUP;       // 上拉（默认高电平，检测下降沿更稳定）
        gpio_initstruct.Speed=GPIO_SPEED_FREQ_HIGH; 
        HAL_GPIO_Init(GPIOA,&gpio_initstruct); 
        

        HAL_NVIC_SetPriority(TIM2_IRQn,2,2);
        HAL_NVIC_EnableIRQ(TIM2_IRQn);
    }
}

/**
  * @brief  TIM2中断服务函数
  * @retval 无
  */
void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&ic_handle);
}

/**
  * @brief  输入捕获回调函数（下降沿触发）
  * @param  htim: 定时器句柄
  * @retval 无
  */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    printf("DOWN");
}
