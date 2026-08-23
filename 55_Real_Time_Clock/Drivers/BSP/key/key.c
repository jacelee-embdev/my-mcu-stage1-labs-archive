#include "key.h"
#include "sys.h"
#include "delay.h"

//初始化GPIO
void KeyInit(void)
{
    GPIO_InitTypeDef gpio_initstruct;
    
    //打开时钟
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    //调用GPIO初始化函数
    gpio_initstruct.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
    gpio_initstruct.Mode=GPIO_MODE_INPUT;
    gpio_initstruct.Pull=GPIO_PULLUP;
    gpio_initstruct.Speed=GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA,&gpio_initstruct);
}

//函数:按键状态扫描
uint8_t KeyScan(void)
{
    /* KEY1 */
    //检测按键是否按下
    if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==GPIO_PIN_RESET)
    {
        //消抖
        delay_ms(88);
        
        //再次检测按键是否按下
        if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==GPIO_PIN_RESET)
       {
            //已按下,等待松开
           while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==GPIO_PIN_SET);
        
           //返回按键值
           return KEY_SET;
        }
    }
    
    
    /* KEY2 */
    //检测按键是否按下
    if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==GPIO_PIN_RESET)
    {
        //消抖
        delay_ms(80);
        
        //再次检测按键是否按下
        if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==GPIO_PIN_RESET)
       {
            //已按下,等待松开
           while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==GPIO_PIN_SET);
        
           //返回按键值
           return KEY_SHIFT;
        }
    }
    
    /* KEY3 */
    //检测按键是否按下
    if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==GPIO_PIN_RESET)
    {
        //消抖
        delay_ms(80);
        
        //再次检测按键是否按下
        if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==GPIO_PIN_RESET)
       {
            //已按下,等待松开
           while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==GPIO_PIN_SET);
        
           //返回按键值
           return KEY_UP;
        }
    }
    
    /* KEY4 */
    //检测按键是否按下
    if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3)==GPIO_PIN_RESET)
    {
        //消抖
        delay_ms(80);
        
        //再次检测按键是否按下
        if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3)==GPIO_PIN_RESET)
       {
            //已按下,等待松开
           while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3)==GPIO_PIN_SET);
        
           //返回按键值
           return KEY_DOWN;
        }
    }
    //其他情况.返回默认值
    return 0;
}
