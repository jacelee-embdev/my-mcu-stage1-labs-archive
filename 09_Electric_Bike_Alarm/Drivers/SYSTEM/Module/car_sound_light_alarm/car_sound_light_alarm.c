#include "car_sound_light_alarm.h"
#include "relay_alarm.h"
#include "delay.h"
#include "led.h"


//函数:锁车声光
void lock_car_alarm(void)
{
    // 第一声短鸣
    Led1_ON();
    relay_alarm_ON();
    delay_ms(100);
    Led1_OFF();
    relay_alarm_OFF();
    delay_ms(120);
    
    // 第二声短鸣
    Led1_ON();
    relay_alarm_ON();
    delay_ms(100);
    Led1_OFF();
    relay_alarm_OFF();
    delay_ms(120);
    
    // 第三声长鸣
    Led1_ON();
    relay_alarm_ON();
    delay_ms(600);
    Led1_OFF();
    relay_alarm_OFF();
    delay_ms(300);
}


//函数:解锁声光
void unlock_car_alarm(void)
{
    // 第一声长鸣
    Led2_ON();
    relay_alarm_ON();
    delay_ms(600);
    Led2_OFF();
    relay_alarm_OFF();
    delay_ms(150);  // 短间隔
    
    // 第二声短鸣
    Led2_ON();
    relay_alarm_ON();
    delay_ms(100);
    Led2_OFF();
    relay_alarm_OFF();
    delay_ms(150);  // 短间隔
    
    // 第三声短鸣
    Led2_ON();
    relay_alarm_ON();
    delay_ms(100);
    Led2_OFF();
    relay_alarm_OFF();
    delay_ms(300);  // 结束间隔
}

//函数:警告声光
void car_theft_alarm(void)
{
    unsigned int total_time = 0;  // 累计时长（单位：ms）
    
    // 第一阶段
    while (total_time < 3000)
    {
        Led1_ON();
        Led2_OFF();
        relay_alarm_ON();
        delay_ms(100);
        
        Led1_OFF();
        Led2_ON();
        relay_alarm_OFF();
        delay_ms(100);
        
        total_time += 200;  // 单次循环200ms
    }
    
    // 第二阶段
    while (total_time < 6000)
    {
        Led1_ON();
        Led2_OFF();
        relay_alarm_ON();
        delay_ms(200);
        
        Led1_OFF();
        Led2_ON();
        relay_alarm_OFF();
        delay_ms(300);
        Led2_OFF();
        
        total_time += 500;  // 单次循环500ms
    }
    
    // 报警结束后复位
    relay_alarm_OFF();
}
