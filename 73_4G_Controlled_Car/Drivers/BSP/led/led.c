#include "led.h"
#include "sys.h"

//初始化GPIO口
void LedInit(void)
{
    GPIO_InitTypeDef gpio_initstruct;
    
    //打开时钟
    __HAL_RCC_GPIOB_CLK_ENABLE();
    
    //调用GPIO初始化函数
    gpio_initstruct.Pin=GPIO_PIN_8|GPIO_PIN_9;
    gpio_initstruct.Mode=GPIO_MODE_OUTPUT_PP;
    gpio_initstruct.Pull=GPIO_PULLUP;
    gpio_initstruct.Speed=GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB,&gpio_initstruct);
    
    //关闭LED
    Led1_OFF();
    Led2_OFF();
}
    

 /* LED1 */
//函数:点亮LED1
void Led1_ON(void)
{
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_RESET);
}

//函数:熄灭LED1
void Led1_OFF(void)
{
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_SET);
}

//函数:翻转LED1的状态
void Led1Toggle(void)
{
    HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_8);
}


    /* LED2 */
//函数:点亮LED2
void Led2_ON(void)
{
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_RESET);
}

//函数:熄灭LED2
void Led2_OFF(void)
{
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_SET);
}

//函数:翻转LED2的状态
void Led2Toggle(void)
{
    HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_9);
}
