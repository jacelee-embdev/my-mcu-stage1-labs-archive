#ifndef __EXTI_VIBRATING_SENSOR_H__
#define __EXTI_VIBRATING_SENSOR_H__

#include "stdint.h"

#define TRUE 1
#define FALSE 0

void exti_vibrating_sensor(void );
uint8_t get_vibrate_flag(void);

void set_vibrate_flag(uint8_t value);

#endif
