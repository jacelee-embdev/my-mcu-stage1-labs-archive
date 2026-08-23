#include "beep.h"
#include "delay.h"

/**
 * @brief 初始化蜂鸣器 GPIO
 */
void beep_init(void)
{
    GPIO_InitTypeDef gpio_initstruct;
    
    BEEP_PORT_CLK_ENABLE();
    
    gpio_initstruct.Pin   = BEEP_PIN;
    gpio_initstruct.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio_initstruct.Pull  = GPIO_PULLUP;
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(BEEP_PORT, &gpio_initstruct);
    
    beep_off(); // 默认关闭
}

void beep_on(void)
{
    HAL_GPIO_WritePin(BEEP_PORT, BEEP_PIN, BEEP_ON_LEVEL);
}

void beep_off(void)
{
    HAL_GPIO_WritePin(BEEP_PORT, BEEP_PIN, BEEP_OFF_LEVEL);
}

/**
 * @brief 蜂鸣器警报声
 */
void beep_alarm(void)
{
    beep_on(); delay_ms(500); beep_off(); delay_ms(250);
    beep_on(); delay_ms(250); beep_off(); delay_ms(250);
}

/**
 * @brief 蜂鸣器功能测试 (小星星旋律)
 */
void beep_test(void)
{
    // 基础节拍控制：1-1-5-5 | 6-6-5-
    beep_on(); delay_ms(500); beep_off(); delay_ms(250); 
    beep_on(); delay_ms(500); beep_off(); delay_ms(250); 
    beep_on(); delay_ms(500); beep_off(); delay_ms(250); 
    beep_on(); delay_ms(500); beep_off(); delay_ms(250); 

    beep_on(); delay_ms(500); beep_off(); delay_ms(250); 
    beep_on(); delay_ms(500); beep_off(); delay_ms(250); 
    beep_on(); delay_ms(500); beep_off(); delay_ms(500); 

    // 4-4-3-3 | 2-2-1-
    beep_on(); delay_ms(500); beep_off(); delay_ms(250); 
    beep_on(); delay_ms(500); beep_off(); delay_ms(250); 
    beep_on(); delay_ms(500); beep_off(); delay_ms(250); 
    beep_on(); delay_ms(500); beep_off(); delay_ms(250); 

    beep_on(); delay_ms(500); beep_off(); delay_ms(250); 
    beep_on(); delay_ms(500); beep_off(); delay_ms(250); 
    beep_on(); delay_ms(500); beep_off(); delay_ms(500); 

    beep_off(); delay_ms(1000);
}
