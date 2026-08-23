#ifndef __LPWR_H__
#define __LPWR_H__

#include "sys.h"

void lpwr_init(void);
void lpwr_enter_sleep_mode(void);
void lpwr_enter_stop_mode(void);
void lpwr_enter_standby_mode(void);

#endif
