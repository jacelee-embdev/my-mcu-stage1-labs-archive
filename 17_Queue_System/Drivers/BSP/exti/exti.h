#ifndef __EXTI_H__
#define __EXTI_H__

#include "stdint.h"

#define TRUE 1
#define FALSE 0

void exti_init(void );
uint8_t get_infrared_sensor_flag(void);
void set_infrared_sensor_flag(uint8_t value);
uint8_t get_infrared_sensor_status(void);
    
#endif
