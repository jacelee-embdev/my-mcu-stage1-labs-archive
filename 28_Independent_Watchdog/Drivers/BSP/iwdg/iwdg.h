#ifndef __IWDG_H__
#define __IWDG_H__

#include "stdint.h"
void iwdg_init(uint8_t psc,uint16_t rlr);
void iwdg_feed(void);
void iwdg_test(void);

#endif
