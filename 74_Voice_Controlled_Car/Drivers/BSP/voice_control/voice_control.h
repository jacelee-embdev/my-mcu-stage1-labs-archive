#ifndef __VOICE_CONTROL_H__
#define __VOICE_CONTROL_H__

#include "sys.h"

#define PIN_1   HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2)
#define PIN_2   HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)
#define PIN_3   HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)

void voice_control_init(void);

#endif
