#ifndef __RTC_H__
#define __RTC_H__

#include "sys.h"
#include "time.h"

void rtc_init(void);
uint16_t rtc_read_bkr(uint8_t bkr_x);
void rtc_write_bkr(uint8_t bkr_x,uint16_t data);
void rtc_get_time(void);
void rtc_set_time(struct tm time_data);
void rtc_set_alarm(struct tm time_data);

#endif
