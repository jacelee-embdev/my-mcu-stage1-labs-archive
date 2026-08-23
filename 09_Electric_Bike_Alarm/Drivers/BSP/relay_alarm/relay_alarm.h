#ifndef __RELAY_ALARM_H__
#define __RELAY_ALARM_H__

#include "stdint.h"

#define RELAY_ALARM_ON  1
#define RELAY_ALARM_OFF 0

void relay_alarm_init(void);
void relay_alarm_ON(void);
void relay_alarm_OFF(void);

uint8_t get_relay_alarm_status(void);
    
#endif
