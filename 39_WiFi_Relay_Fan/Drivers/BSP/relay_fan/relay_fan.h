#ifndef __RELAY_FAN_H__
#define __RELAY_FAN_H__

#include "stdint.h"

#define RELAY_FAN_ON  0
#define RELAY_FAN_OFF 1

void relay_fan_init(void);
void relay_fan_ON(void);
void relay_fan_OFF(void);

#endif
