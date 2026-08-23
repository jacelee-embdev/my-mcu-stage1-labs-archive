#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "motor.h"
#include "speed.h"
#include "oled.h"
#include "esp8266.h"
#include "string.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    LedInit();
    uart1_init(115200);  
    motor_init();
    speed_init();
    oled_init();
    esp8266_init(115200);
    printf("Hello World!\n");
  
    
   char recv_data[ESP8266_RX_BUF_SIZE];
    while(1)
    {
        esp8266__receive_data(recv_data);
        if(strstr(recv_data,"M1") != NULL)
        {
            motor_go_forward();
        }
        else if(strstr(recv_data,"M2") != NULL)
        {
            motor_go_backward();
        }
        else if(strstr(recv_data,"M3") != NULL)
        {
            motor_go_left();
        }
        else if(strstr(recv_data,"M4") != NULL)
        {
            motor_go_right();
        }
        else
        {
            motor_stop();
        }
        
        delay_ms(10);
    }
} 
