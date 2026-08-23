#include "led.h"
#include "sys.h"

//初始化GPIO口
void LedInit(void)
{
    GPIO_InitTypeDef gpio_initstruct;
    
    //打开时钟
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    //调用GPIO初始化函数
    gpio_initstruct.Pin=GPIO_PIN_0;
    gpio_initstruct.Mode=GPIO_MODE_OUTPUT_PP;
    gpio_initstruct.Pull=GPIO_PULLUP;
    gpio_initstruct.Speed=GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA,&gpio_initstruct);
    
    //关闭LED
}
    
//函数:点亮LED
void Led_ON(void)
{
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET);
}

//函数:熄灭LED
void Led_OFF(void)
{
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET);
}

//函数:翻转LED的状态
void LedToggle(void)
{
    HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_0);
}
