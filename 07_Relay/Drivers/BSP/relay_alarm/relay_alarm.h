#ifndef __RELAYALARM_H__
#define __RELAYALARM_H__

#include "stdint.h"

#define RELAY_ALARM_ON  0
#define RELAY_ALARM_OFF 1

void relay_alarm_init(void);
void relay_alarm_ON(void);
void relay_alarm_OFF(void);
#endif
