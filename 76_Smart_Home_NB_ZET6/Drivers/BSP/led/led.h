#ifndef __LED_H__
#define __LED_H__

#include "sys.h"

/* --- 硬件接口定义 (移植时仅需修改此处) --- */
#define LED_PWM_TIM_INSTANCE            TIM3                            // 定时器实例
#define LED_PWM_TIM_CLK_ENABLE()        __HAL_RCC_TIM3_CLK_ENABLE()     // 定时器时钟使能
#define LED_PWM_TIM_CHANNEL             TIM_CHANNEL_3                   // PWM 通道

#define LED_PWM_GPIO_PORT               GPIOB                           // GPIO 端口
#define LED_PWM_GPIO_PIN                GPIO_PIN_0                      // GPIO 引脚
#define LED_PWM_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOB_CLK_ENABLE()    // GPIO 时钟使能

/* --- 函数声明 --- */
void led_init(void);            // 初始化 LED (PWM)
void led_on(void);
void led_off(void);             // 关闭
void led_brightness_up(void);
void led_brightness_down(void);
void led_brightness_auto(float lux_val);
uint8_t led_level_get(void);    // 获取当前档位
void led_test(void);            // 测试函数

#endif
