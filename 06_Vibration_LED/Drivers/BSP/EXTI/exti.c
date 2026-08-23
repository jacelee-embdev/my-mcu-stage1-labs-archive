#include "exti.h"
#include "sys.h"
#include "delay.h"
#include "led.h"

uint8_t vibrate_flag = FALSE;

//函数:中断初始化
void exti_init(void )
{
    GPIO_InitTypeDef gpio_initstruct;
    
    //打开时钟
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    //调用GPIO初始化函数
    gpio_initstruct.Pin=GPIO_PIN_4;
    gpio_initstruct.Mode=GPIO_MODE_IT_FALLING;
    gpio_initstruct.Pull=GPIO_PULLUP;
    gpio_initstruct.Speed=GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA,&gpio_initstruct);
    
    // 配置EXTI0中断的优先级（中断通道：EXTI0_IRQn，对应PA0的外部中断）
    HAL_NVIC_SetPriority(EXTI4_IRQn,2,0);
    
    //使能EXTI0中断通道（打开中断的"开关"）
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);
}

//中断服务函数(ISR)
void EXTI4_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
}

//中断回调函数（Callback）
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin==GPIO_PIN_4)
    {
        if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)==GPIO_PIN_RESET)
            vibrate_flag = TRUE;
    }
}

//函数:把"标志位"的值传出去
uint8_t get_vibrate_flag(void)
{
   uint8_t temp=vibrate_flag;   //temp的妙用
    vibrate_flag=FALSE;
    return temp;
}

//函数:在它处修改"标志位的值"
void set_vibrate_flag(uint8_t value)
{
    vibrate_flag=value;
}
