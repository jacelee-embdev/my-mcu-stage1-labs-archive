#include "sys.h"
#include "delay.h"
#include "led.h"
#include "exti.h"
#include "relay_alarm.h"
#include "car_sound_light_alarm.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9);     /* 设置时钟, 72Mhz */
    LedInit();                          //初始化LED
    exti_init();                        //初始化EXTI
    relay_alarm_init();                 //初始化给蜂鸣器的继电器
    
    uint8_t relay_alarm_mode= FALSE ;
    
    while(1)
    { 
        //监测A键是否按下
        if(get_buttonA_flag() == TRUE)
        {
            relay_alarm_mode= TRUE ;
            lock_car_alarm();   //锁车

        }
        
        //监测B键是否按下
        if(get_buttonB_flag() == TRUE)
        {
            if(get_relay_alarm_status() == RELAY_ALARM_ON)
            {
                delay_ms(1000);
                unlock_car_alarm(); //开锁
            }
            else
            {
                unlock_car_alarm(); //开锁
            }
            relay_alarm_mode= FALSE ;
        }

        //处于警戒模式时
        if(relay_alarm_mode == TRUE)
        {
            // 实时检测震动：PA4低电平（GPIO_PIN_RESET）= 震动，高电平=无震动
            if(get_vibrate_status() == GPIO_PIN_RESET)
            {
                car_theft_alarm();  // 震动时蜂鸣器鸣
            }
            else
            {
                relay_alarm_OFF();  // 震动停止时蜂鸣器停
            }
        }
        else
        {
            //set_vibrate_flag(FALSE);// 振动传感器标志位置为0
            relay_alarm_OFF();      // 非警戒模式强制关闭蜂鸣器
        }
    }
}
