#include "voice_control.h"

void voice_control_init(void)
{
    GPIO_InitTypeDef gpio_initstruct;
    
    //打开时钟
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    //调用GPIO初始化函数
    gpio_initstruct.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2;
    gpio_initstruct.Mode=GPIO_MODE_INPUT;
//    gpio_initstruct.Pull=GPIO_PULLUP;
    gpio_initstruct.Speed=GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA,&gpio_initstruct);
    
}
