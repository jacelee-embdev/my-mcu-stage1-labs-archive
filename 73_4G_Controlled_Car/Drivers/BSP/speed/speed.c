#include "speed.h"
#include "stdio.h"
#include "string.h"
#include "oled.h"
#include "bluetooth.h"

uint16_t speed_cnt = 0;
char speed_str[24] = {0};
TIM_HandleTypeDef timer_handle = {0};

void speed_gpio_init(void)
{
     GPIO_InitTypeDef gpio_initstruct;
    
    //打开时钟
    __HAL_RCC_GPIOB_CLK_ENABLE();
    
    //调用GPIO初始化函数
    gpio_initstruct.Pin=GPIO_PIN_12;
    gpio_initstruct.Mode=GPIO_MODE_IT_FALLING;
    gpio_initstruct.Pull=GPIO_NOPULL;
    gpio_initstruct.Speed=GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB,&gpio_initstruct);
    
    // 配置EXTI0中断的优先级（中断通道：EXTI0_IRQn，对应PA0的外部中断）
    HAL_NVIC_SetPriority(EXTI15_10_IRQn,2,0);
    
    //使能EXTI0中断通道（打开中断的"开关"）
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

//中断服务函数(ISR)
void EXTI15_10_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
}


//中断回调函数（Callback）
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin ==GPIO_PIN_12)
    {
        if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12)==GPIO_PIN_RESET)
        {
            speed_cnt++;
//            printf("speed_cnt:%d",speed_cnt);
        }
    }
}



void speed_timer_init(uint16_t arr,uint16_t psc)
{
    timer_handle.Instance = TIM2;                  // 选择TIM2
    timer_handle.Init.Prescaler = psc;             // 设置预分频系数
    timer_handle.Init.Period = arr;                // 设置自动重装值
    timer_handle.Init.CounterMode = TIM_COUNTERMODE_UP;  // 向上计数模式
    timer_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;  // 禁用自动重装预装载

    HAL_TIM_Base_Init(&timer_handle);              // 初始化定时器
    HAL_TIM_Base_Start_IT(&timer_handle);          // 启动定时器并开启中断
}
/**
  * @brief  定时器底层硬件初始化（由HAL库自动调用）
  * @param  htim: 定时器句柄指针
  * @retval 无
  */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM2)
    {
         __HAL_RCC_TIM2_CLK_ENABLE();               // 使能TIM2时钟
        HAL_NVIC_SetPriority(TIM2_IRQn, 2, 2);     // 配置TIM2中断优先级（抢占2，响应2）
        HAL_NVIC_EnableIRQ(TIM2_IRQn);             // 使能TIM2中断;
    }
}

/**
  * @brief  TIM2中断服务函数（中断入口）
  * @retval 无
  */
void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&timer_handle);      // HAL库中断统一处理
}

/**
  * @brief  定时器更新中断回调函数
  * @param  htim: 定时器句柄指针
  * @retval 无
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM2)
    {
        printf("speed:%d\r\n",speed_cnt);
        memset(speed_str,0,sizeof(speed_str));
        sprintf(speed_str,"speed:%2d cm/s",speed_cnt);
        oled_show_string(10,2,speed_str,16);
        bluetooh_send(speed_str);
        bluetooh_send("\r\n");
        speed_cnt = 0;
    }
}


void speed_init(void)
{
    speed_gpio_init();
    speed_timer_init(1000-1,7200-1);
}
