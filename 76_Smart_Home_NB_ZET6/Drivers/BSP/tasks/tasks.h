#ifndef __TASKS_H__
#define __TASKS_H__

#include "sys.h"

// --- LED工作模式 ---
typedef enum
{
    MODE_AUTO = 0,   // 智能感光模式
    MODE_BT_CTRL,    // 蓝牙/语音手动模式
} LedMode_t;

void timer_ISR(void);

// 任务声明：注意 1,4,5 号任务增加了指令参数
void task1_led_control(uint8_t cmd);
void task2_gas_alarm(void);
void task3_temphum_upload(void);
void task4_fan_ctrl(uint8_t cmd);
void task5_lock_ctrl(uint8_t cmd);

#endif
