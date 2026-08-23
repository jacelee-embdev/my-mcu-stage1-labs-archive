#ifndef __KEY_H__
#define __KEY_H__
#include "sys.h"

enum key_num
{
    KEY_SET =1,
    KEY_SHIFT,
    KEY_UP,
    KEY_DOWN
};

void KeyInit(void);
uint8_t KeyScan(void);

#endif
