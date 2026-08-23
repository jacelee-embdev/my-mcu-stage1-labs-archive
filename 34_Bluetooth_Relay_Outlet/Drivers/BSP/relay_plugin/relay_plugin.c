#include "sys.h"
#include "relay_plugin.h"


//初始化GPIO口
void relay_plugin_init(void)
{
    GPIO_InitTypeDef gpio_initstruct;
    
    //打开时钟
    __HAL_RCC_GPIOB_CLK_ENABLE();
    
    //调用GPIO初始化函数
    gpio_initstruct.Pin=GPIO_PIN_6;
    gpio_initstruct.Mode=GPIO_MODE_OUTPUT_PP;
    gpio_initstruct.Pull=GPIO_PULLUP;
    gpio_initstruct.Speed=GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB,&gpio_initstruct);
    
    //关闭relay_plugin
    relay_plugin_OFF();
}
    
//函数:打开relay_plugin
void relay_plugin_ON(void)
{
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET);
}

//函数:关闭relay_plugin
void relay_plugin_OFF(void)
{
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET);
}

//获取继电器当前状态
uint8_t relay_plugin_status_get()
{
    return (uint8_t)HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6);
}
