#include "sys.h"
#include "delay.h"
#include "uart1.h"
#include "beep.h"
#include "key.h"
#include "oled.h"
#include "rtc.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    uart1_init(115200);
    BeepInit();
    KeyInit();
    oled_init();
    rtc_init();
    printf("Hello World!\n");
    oled_show_init();
    
    uint8_t time_data[6] = {26,01,26,23,22,00};
    uint8_t alarm_time_data[3] = {6,40,00};
    
    uint8_t set_time_shift = TIME_YEAR;
    uint8_t set_alarm_time_shift = ALARM_HOUR;
    
    uint8_t set_time_flag = 0;
    uint8_t set_alarm_time_flag = 0;
    
    if(rtc_read_bkr(1) != 0XA5A5)
    {
        rtc_write_bkr(1,0XA5A5);
        
        rtc_set_time(time_data);
        rtc_set_alarm(alarm_time_data);
    }
    
    while(1)
    {
        //获取时间及闹钟时间
        rtc_get_time(time_data);
        rtc_get_alarm(alarm_time_data);
        //在OLED上显示时间及闹钟时间
        oled_show_time_and_alarm_time(time_data,alarm_time_data);
        
        switch(KeyScan())
        {
            case KEY_SET:
                //进入时间设置模式
                set_time_flag =1;
                while(set_time_flag)
                {
                    //闪烁要修改的时间
                    oled_show_element(time_data[set_time_shift],OFF,set_time_shift);
                    delay_ms(100);
                    oled_show_element(time_data[set_time_shift],ON,set_time_shift);
                    delay_ms(100);
                    switch(KeyScan())
                    {
                        case KEY_SET:
                            //保存并退出设置
                            set_time_flag =0;
                            rtc_set_time(time_data);
                            set_time_shift = TIME_YEAR;
                            break;
                        case KEY_SHIFT:
                            //跳转至下一个要修改的时间元素(秒->分->时->月->年)
                            if(set_time_shift++ >= TIME_SECOND)
                            {
                                set_time_shift = TIME_YEAR;
                            }
                            break;
                        case KEY_UP:
                            //增加该时间元素
                            if(set_time_shift == TIME_YEAR)
                            {
                                if(time_data[set_time_shift] < 100-1)
                                {
                                    time_data[set_time_shift]++;
                                }
                            }
                            else if(set_time_shift == TIME_MONTH)
                            {
                                if(time_data[set_time_shift] < 12)
                                {
                                    time_data[set_time_shift]++;
                                }
                            }
                            else if(set_time_shift == TIME_DAY)
                            {
                                if(time_data[set_time_shift] < 31)
                                {
                                    time_data[set_time_shift]++;
                                }
                            }
                            else if(set_time_shift == TIME_HOUR)
                            {
                                if(time_data[set_time_shift] < 24-1)
                                {
                                    time_data[set_time_shift]++;
                                }
                            }
                            else if(set_time_shift == TIME_MINUTE || set_time_shift == TIME_SECOND)
                            {
                                if(time_data[set_time_shift] < 60-1)
                                {
                                    time_data[set_time_shift]++;
                                }
                            }
                            break;
                        case KEY_DOWN:
                            //减小该时间元素
                            if(time_data[set_time_shift] > 0)
                            {
                                time_data[set_time_shift]--;
                            }
                            break;
                    }
                }
                break;
                
                
            case KEY_SHIFT:
                //进入闹钟设置模式
                set_alarm_time_flag = 1;
                while(set_alarm_time_flag)
                {
                    oled_show_element(alarm_time_data[set_alarm_time_shift-ALARM_HOUR],OFF,set_alarm_time_shift);
                    delay_ms(100);
                    oled_show_element(alarm_time_data[set_alarm_time_shift-ALARM_HOUR],ON,set_alarm_time_shift);
                    delay_ms(100);
                    switch(KeyScan())
                    {
                        case KEY_SET:
                            //保存闹钟配置并退出设置
                            rtc_set_alarm(alarm_time_data);
                            set_alarm_time_flag = 0;
                            set_alarm_time_shift = ALARM_HOUR;
                            break;
                        case KEY_SHIFT:
                            //跳转至下一个需要修改选项
                            if(set_alarm_time_shift++ >= ALARM_SECOND)
                            {
                                set_alarm_time_shift = ALARM_HOUR;
                            }
                            break;
                        case KEY_UP:
                            //+1该选项
                        if(alarm_time_data[set_alarm_time_shift-ALARM_HOUR] < 59)
                        {
                            alarm_time_data[set_alarm_time_shift-ALARM_HOUR]++;
                        }
                            break;
                        case KEY_DOWN:
                            //-1改选项
                        if(alarm_time_data[set_alarm_time_shift-ALARM_HOUR] > 0)
                        {
                            alarm_time_data[set_alarm_time_shift-ALARM_HOUR]--;
                        }
                            break;
                        default:
                            break;
                    }
                }
                break;
            case KEY_UP:
                break;
            case KEY_DOWN:
                //停止蜂鸣器
                break;
            default:
                break;
        }
    }
}

//switch(KeyScan())
//        {
//            case KEY_SET:
//                break;
//            case KEY_SHIFT:
//                break;
//            case KEY_UP:
//                break;
//            case KEY_DOWN:
//                break;
//            default:
//                break;
//        }

