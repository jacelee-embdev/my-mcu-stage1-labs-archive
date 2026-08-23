#ifndef __RELAY_GATE_H__
#define __RELAY_GATE_H__

#include "stdint.h"

#define RELAY_GATE_ON  0
#define RELAY_GATE_OFF 1

void relay_gate_init(void);
void relay_gate_ON(void);
void relay_gate_OFF(void);
#endif
