#ifndef __BEEP_H__
#define __BEEP_H__

#include "sys.h"

/* 硬件移植定义区 */
#define BEEP_PORT                GPIOE
#define BEEP_PIN                 GPIO_PIN_0
#define BEEP_PORT_CLK_ENABLE()   __HAL_RCC_GPIOE_CLK_ENABLE()

/* 逻辑电平定义（低电平触发） */
#define BEEP_ON_LEVEL            GPIO_PIN_RESET
#define BEEP_OFF_LEVEL           GPIO_PIN_SET

/* 函数声明 */
void beep_init(void);    // 初始化蜂鸣器引脚
void beep_on(void);      // 开启蜂鸣器
void beep_off(void);     // 关闭蜂鸣器
void beep_alarm(void);    // 蜂鸣器警报音效
void beep_test(void);    // 播放测试音效

#endif
