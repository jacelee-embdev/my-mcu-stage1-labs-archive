#include "track.h"
#include "delay.h"
#include "led.h"


//函数:中断初始化
void track_init(void )
{
    GPIO_InitTypeDef gpio_initstruct;
    
    //打开时钟
    __HAL_RCC_GPIOB_CLK_ENABLE();
    
    //调用GPIO初始化函数
    gpio_initstruct.Pin=GPIO_PIN_13 | GPIO_PIN_14;
    gpio_initstruct.Mode=GPIO_MODE_INPUT;
    gpio_initstruct.Pull=GPIO_PULLUP;
    gpio_initstruct.Speed=GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB,&gpio_initstruct);
}

uint8_t get_left_track_flag(void)
{
    if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13) == GPIO_PIN_RESET)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

uint8_t get_right_track_flag(void)
{
    if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14) == GPIO_PIN_RESET)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
