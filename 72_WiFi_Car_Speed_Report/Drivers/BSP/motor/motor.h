#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "sys.h"

void motor_init(void);
void motor_go_forward(void);
void motor_go_backward(void);
void motor_go_left(void);
void motor_go_right(void);
void motor_stop(void);

#endif
