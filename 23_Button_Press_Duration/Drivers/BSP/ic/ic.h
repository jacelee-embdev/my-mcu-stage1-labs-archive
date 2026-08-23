#ifndef __IC_H__
#define __IC_H__

#include "stdint.h"
#include "sys.h"

void ic_init(uint16_t arr,uint16_t psc);
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim);
void TIM2_IRQHandler(void);
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);
void get_pressed_time(void);


#endif
