#ifndef __TASKS_H__
#define __TASKS_H__

void SysTick_ISR(void);

void led1_task(void);
void led2_task(void);
void lcd1602_task(void);
void alarm_bee_task(void);

#endif
