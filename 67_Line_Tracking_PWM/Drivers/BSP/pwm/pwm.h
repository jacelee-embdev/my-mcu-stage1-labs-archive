#ifndef __PWM_LED_H__
#define __PWM_LED_H__

#include "stdint.h"

void pwm_init(uint16_t arr,uint16_t psc);

void set_pwm_compare(uint16_t val);
void set_left_motor_pwm(uint16_t val);
void set_right_motor_pwm(uint16_t val);

#endif
