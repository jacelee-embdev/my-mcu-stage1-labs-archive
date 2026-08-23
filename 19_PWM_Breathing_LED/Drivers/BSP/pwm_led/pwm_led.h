#ifndef __PWM_LED_H__
#define __PWM_LED_H__

#include "stdint.h"

// PWM初始化函数
void pwm_init(uint16_t arr,uint16_t psc);

// 设置PWM占空比函数
void set_pwm_compare(uint16_t val);

#endif
