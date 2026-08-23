#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "esp8266.h"
#include "key.h"
#include "oled.h"
#include "cJSON.h"
#include "weather.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    LedInit();
    uart1_init(115200);
    esp8266_init(115200);
    KeyInit();
    oled_init();
    printf("Hello World!\n");
  
    oled_show_init();
    
    get_3days_weather();
    show_weather(2);
    
//    esp8266_get_weather(0);
    uint8_t key_num = 0;
    uint8_t day = 0;
    while(1)
    {
        key_num = KeyScan();
        if(key_num == 1)
        {
            day++;
            day %= 3;
            show_weather(day);
            
        }
        else if(key_num == 2)
        {
            printf("更新天气...:");
            get_3days_weather();
            show_weather(0);
            day = 0;
        }
        Led1_ON();
        Led2_OFF();
        delay_ms(500);
        Led1_OFF();
        Led2_ON();
        delay_ms(500);
    }
}
