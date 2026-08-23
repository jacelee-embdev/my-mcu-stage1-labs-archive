#include "trash_bin_ctrl_core.h"
#include "sys.h"
#include "delay.h"
#include "uart1.h"
#include "led.h"
#include "beep.h"
#include "exti_vibrating_sensor.h"
#include "hcsr04.h"
#include "key.h"
#include "pwm_sg90.h" 

// 垃圾桶状态标志，初始为关闭（CLOSE/OPEN为状态宏定义
uint8_t trash_bin_status_flag = CLOSE;

// 开盖操作：仅关闭时执行，控制舵机+声光提示+更新状态
void open_trash_bin(void)
{
    if(trash_bin_status_flag == CLOSE)
    {
        set_sg90_angle(180 );
        Beep_ON();
        Led2_ON();
        delay_ms(100);
        Beep_OFF();
        Led2_OFF();
        Led1_ON();// LED1亮（标识开盖）
        trash_bin_status_flag = OPEN;// 更新为开盖状态
    }
}

// 关盖操作：控制舵机+重置指示灯+更新状态
void close_trash_bin(void)
{
    set_sg90_angle(0);
    Beep_OFF();
    Led1_OFF();
    Led2_ON();// LED2亮（标识关盖）
    trash_bin_status_flag = CLOSE;// 更新为关盖状态
}

// 获取垃圾桶当前状态（CLOSE/OPEN）
uint8_t get_trash_bin_status_flag(void)
{
    return trash_bin_status_flag;
}

// 设置垃圾桶状态标志（仅改标志，不操作硬件）
void set_trash_bin_status_flag(uint8_t val)
{
    trash_bin_status_flag = val;
}
