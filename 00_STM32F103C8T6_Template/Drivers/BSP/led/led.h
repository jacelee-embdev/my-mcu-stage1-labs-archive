#ifndef __LED_H__
#define __LED_H__

#include "sys.h"

// 硬件引脚宏定义
#define LED_PIN                  GPIO_PIN_4
#define LED_PORT                 GPIOA
#define LED_CLK_ENABLE()         __HAL_RCC_GPIOA_CLK_ENABLE()

// 函数声明
void led_init(void);
void led_on(void);
void led_off(void);
void led_toggle(void);

#endif
