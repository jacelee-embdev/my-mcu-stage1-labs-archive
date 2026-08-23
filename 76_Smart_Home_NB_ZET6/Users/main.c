#include "sys.h"
#include "delay.h"
#include "usart1.h"
#include "keyboard.h"
#include "beep.h"
#include "oled.h"
#include "w25q128.h"
#include "password.h"
#include "oled_ui.h"
#include "tasks.h"
#include "timer.h"
#include "adc.h"
#include "bluetooth.h"
#include "led.h"
#include "voice.h"
#include "esp8266.h"
#include "dht11.h"
#include "onenet.h"
#include "motor.h"

void System_Init_All(void);

int main(void)
{
    System_Init_All();
    printf("Hello Word!\r\n");

//    w25q128_chip_erase();

    uint8_t key_last = 0;

    password_check();

    while(1)
    {
        oled_show_input();
        key_last = password_get_input();
        
        if(key_last == POUND_KEY)
        {
            if(password_compare() == TRUE)
            {
                password_input_right_operate();
            }
            else
            {
                password_input_wrong_operate();
            }
        }
        else if(key_last == START_KEY)
        {
            oled_show_old();
            password_get_input();
            if(password_compare() == TRUE)
            {
                password_old_right_operate();
            }
            else
            {
                password_old_wrong_operate();
            }
        }
        delay_ms(500);
    }
}


void System_Init_All(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    SystemClock_Config(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    usart1_init(115200);
    keyboard_init();
    beep_init();
    oled_init();
    w25q128_init();
    password_init();
    timer_init(5000-1,7200-1);  //500ms中断一次
    adc_dma_init();
    bluetooth_init(115200);
    led_init();
    voice_init();
    motor_init();
    esp8266_init(115200);
    
    printf("MQTT初始化...\r\n");
    mqtt_init();
    
    printf("MQTT连接...\r\n");
    mqtt_connect(MQTT_ClientID,MQTT_UserName,MQTT_PassWord);
}