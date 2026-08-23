#ifndef __RELAY_LOCK_H__
#define __RELAY_LOCK_H__

#include "stdint.h"

#define RELAY_GATE_ON  0
#define RELAY_GATE_OFF 1

void relay_lock_init(void);
void relay_lock_ON(void);
void relay_lock_OFF(void);
#endif
