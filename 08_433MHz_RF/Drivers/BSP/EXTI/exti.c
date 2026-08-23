#include "exti.h"
#include "sys.h"
#include "delay.h"
#include "led.h"

uint8_t buttonA_flag=0;
uint8_t buttonB_flag=0;

//函数:中断初始化
void exti_init(void )
{
    GPIO_InitTypeDef gpio_initstruct;
    
    //打开时钟
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    
    /* 初始化PIN_A12 */
    //调用GPIO初始化函数
    gpio_initstruct.Pin=GPIO_PIN_12;
    gpio_initstruct.Mode=GPIO_MODE_IT_RISING;   //上升沿触发
    gpio_initstruct.Pull=GPIO_PULLDOWN;
    gpio_initstruct.Speed=GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA,&gpio_initstruct);
    // 配置EXTI15-10中断的优先级
    HAL_NVIC_SetPriority(EXTI15_10_IRQn,2,0);
    //使能EXTI15-10中断通道（打开中断的"开关"）
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
    
    
    
    /* 初始化PIN_B5 */
    //调用GPIO初始化函数
    gpio_initstruct.Pin=GPIO_PIN_5;
    gpio_initstruct.Mode=GPIO_MODE_IT_RISING;   //上升沿触发
    gpio_initstruct.Pull=GPIO_PULLDOWN;
    gpio_initstruct.Speed=GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB,&gpio_initstruct);
    // 配置EXTI9-5中断的优先级
    HAL_NVIC_SetPriority(EXTI9_5_IRQn,2,0);
    //使能EXTI9-5中断通道（打开中断的"开关"）
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}

//PIN_A12触发的中断服务函数(ISR)
void EXTI15_10_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
}

//PIN_B5触发的中断服务函数(ISR)
void EXTI9_5_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
}


//中断回调函数（Callback）
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin==GPIO_PIN_12)
    {
        if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12)==GPIO_PIN_SET)
        {
            buttonB_flag=TRUE;
        }
    }
    else if(GPIO_Pin==GPIO_PIN_5)
    {
        if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5)==GPIO_PIN_SET)
        {
            buttonA_flag=TRUE;
        }
    }
}

//函数:读取按键B状态
uint8_t get_buttonB_flag(void)
{
    uint8_t temp=buttonB_flag;
    buttonB_flag=FALSE;
    return temp;
}

//函数:设置按键B状态
void set_buttonB_flag(uint8_t value)
{
    buttonB_flag=value;
}


//函数:读取按键A状态
uint8_t get_buttonA_flag(void)
{
    uint8_t temp=buttonA_flag;
    buttonA_flag=FALSE;
    return temp;
}

//函数:设置按键A状态
void set_buttonA_flag(uint8_t value)
{
    buttonB_flag=value;
}
