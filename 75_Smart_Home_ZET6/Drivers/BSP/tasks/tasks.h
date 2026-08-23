#ifndef __TASKS_H__
#define __TASKS_H__

#include "sys.h"

// --- LED工作模式 ---
typedef enum
{
    MODE_AUTO = 0,   // 智能感光模式
    MODE_BT_CTRL,    // 蓝牙遥控模式
    MODE_VOICE_CTRL,
} LedMode_t;

void timer_ISR(void);

void task_led_control(void);
void task_gas_alarm(void);
void task_temphum_upload(void);
void led_apply_action(uint8_t cmd);

#endif
