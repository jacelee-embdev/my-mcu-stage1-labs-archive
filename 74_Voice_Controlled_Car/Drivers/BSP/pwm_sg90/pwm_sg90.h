#ifndef __PWM_SG90_H__
#define __PWM_SG90_H__

#include "stdint.h"

void sg90_init(void);
void set_sg90_angle(uint16_t angle);
void sg90_turn_left(void);
void sg90_turn_middle(void);
void sg90_turn_right(void);
    
#endif
