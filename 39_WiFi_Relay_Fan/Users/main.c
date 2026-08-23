#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "esp8266.h"
#include "relay_fan.h"
#include "string.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    LedInit();
    uart1_init(115200);
    esp8266_init(115200);
    relay_fan_init();
    printf("Hello World!\n");

    char recv_data[ESP8266_RX_BUF_SIZE];
    while(1)
    {
        esp8266__receive_data(recv_data);
        if(strstr(recv_data, "ON") != NULL)
        {
            relay_fan_ON();
        }
        else if(strstr(recv_data, "OFF") != NULL)
        {
            relay_fan_OFF();
        }
        Led1_ON();
        Led2_OFF();
        delay_ms(500);
        Led1_OFF();
        Led2_ON();
        delay_ms(500);
    }
}
