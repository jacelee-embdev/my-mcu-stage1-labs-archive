#ifndef __TRASH_BIN_CTRL_CORE_H__
#define __TRASH_BIN_CTRL_CORE_H__

#include "stdint.h"
#define OPEN    1
#define CLOSE   0

void open_trash_bin(void);
void close_trash_bin(void);

uint8_t get_trash_bin_status_flag(void);
void set_trash_bin_status_flag(uint8_t val);

#endif
