#include "relay_alarm.h"
#include "sys.h"

//初始化GPIO口
void relay_alarm_init(void)
{
    GPIO_InitTypeDef gpio_initstruct;
    
    //打开时钟
    __HAL_RCC_GPIOB_CLK_ENABLE();
    
    //调用GPIO初始化函数
    gpio_initstruct.Pin=GPIO_PIN_7;
    gpio_initstruct.Mode=GPIO_MODE_OUTPUT_PP;
    gpio_initstruct.Pull=GPIO_PULLUP;
    gpio_initstruct.Speed=GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB,&gpio_initstruct);
    
    //关闭relay_alarm
    relay_alarm_OFF();
}
    
//函数:打开relay_alarm
void relay_alarm_ON(void)
{
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_RESET);
}

//函数:关闭relay_alarm
void relay_alarm_OFF(void)
{
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_SET);
}

//获取继电器当前状态
uint8_t get_relay_alarm_status(void)
{
    return (uint8_t)HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7);
}
