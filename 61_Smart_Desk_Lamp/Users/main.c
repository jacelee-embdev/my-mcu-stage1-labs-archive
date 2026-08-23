#include "sys.h"
#include "delay.h"
#include "uart1.h"
#include "beep.h"
#include "bluetooth.h"
#include "hcsr04.h"
#include "ia_sensor.h"
#include "key.h"
#include "light_sensor.h"
#include "oled.h"
#include "timer.h"
#include "led.h"

enum lamp_mode
{
    AUTO_MODE = 0,
    MANUAL_MODE,
    REMOTE_MODE
};

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    uart1_init(115200);
    BeepInit();
    KeyInit();
    bluetooth_init(115200);
    hcsr04_init();
    light_sensor_init();
    oled_init();
    timer_init(10000-1,7200-1);
    led_init();
    ia_sensor_init();
    printf("Hello World!\n");
  
    uint8_t person_flag = 0;
    uint8_t first_loop = 1;
    uint8_t distance = 0;
    
    uint8_t distance_str[3] = {0};
    uint8_t sit_time_str[3] = {0};
    
    uint8_t key_num = 0;
    uint8_t mode = AUTO_MODE;
    uint8_t light_value = 0;
    uint8_t led_level =0;
    
    uint8_t tst = -1;
    
    oled_show_init();
    while(1)
    {
        person_flag = get_ia_sensor_flag();
        if(person_flag == TRUE)     //有人
        {
            oled_show_Chinese(10,4,9);
            if(first_loop)
            {
                first_loop = 0;
                timer_start();
            }
            
            distance = get_length_from_hcsr04();
            if(distance < 10)
            {
                Beep_ON();
            }
            else
            {
                Beep_OFF();
            }
            
            if(get_sit_time() >=5)
            {
                Beep_ON();
            }
        }
        else                        //无人
        {
            oled_show_Chinese(10,4,10);
            timer_stop();
            set_sit_time(0);
            first_loop = 1;
            Beep_OFF();
            distance = 0;
        }
        
        sprintf((char *)distance_str,"%3d",distance);
        oled_show_string(60,4,(char *)distance_str,16);
        
        sprintf((char *)sit_time_str,"%3d",get_sit_time());
        oled_show_string(60,6,(char *)sit_time_str,16);
        
    key_num = KeyScan();
    if(key_num == 1)
    {
        if(mode++ > 1)
        {
            mode = AUTO_MODE;
        }
    }
    else if(key_num == 3)
    {
        timer_toggle();
    }
    else if(key_num == 4)
    {
        timer_stop();
        set_sit_time(0);
    }

    switch(mode)
    {
        case AUTO_MODE:
        {
            oled_show_Chinese(60,0,3);  //智
            oled_show_Chinese(75,0,4);  //能
            if(person_flag == TRUE)
            {
                light_value =light_sensor_get_value();
                if(light_value < 40 )
                {
                    led_high();
                }
                else if(light_value >= 40 && light_value <= 70)
                {
                    led_medium();
                }
                else if(light_value > 70)
                {
                    led_low(); 
                }
            }
            else
            {
                led_off();
            }
            break;
        }
        case MANUAL_MODE:
        {
            oled_show_Chinese(60,0,5);  //按
            oled_show_Chinese(75,0,6);  //键
            
            if(key_num == 2)
            {
                led_level = led_level_get();
                if(led_level++ > 2)
                {
                    led_level = 0;
                }
            
            switch (led_level)
                {
                    case 0:
                        led_off();
                    case 1:
                        led_low();
                        break;
                    case 2:
                        led_medium();
                        break;
                    case 3:
                        led_high();
                        break;
                    default:
                        break;
                }
            }
            break;
        } 
        case REMOTE_MODE:
        {
            oled_show_Chinese(60,0,7);  //远
            oled_show_Chinese(75,0,8);  //程
            tst = bt_rx_get() - '0';
            printf("command:%d",tst);
            switch (tst)
            {
                case 0:
                    led_off();
                    break;
                case 1:
                    led_low();
                    break;
                case 2:
                    led_medium();
                    break;
                case 3:
                    led_high();
                    break;
                case 4:
                    timer_start();
                    break;
                case 5:
                    timer_stop();
                    break;
                case 6:
                    timer_stop();
                set_sit_time(0);
                    break;
                default:
                    break;
            }
            break;
        }
        default:
            break;
    }
    
    delay_ms(500);
    }
}
