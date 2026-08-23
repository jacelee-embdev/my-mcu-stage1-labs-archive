#ifndef __RELAY_PLUGIN_H__
#define __RELAY_PLUGIN_H__

#include "stdint.h"

#define RELAY_PLUGIN_ON  0
#define RELAY_PLUGIN_OFF 1

void relay_plugin_init(void);
void relay_plugin_ON(void);
void relay_plugin_OFF(void);

#endif
