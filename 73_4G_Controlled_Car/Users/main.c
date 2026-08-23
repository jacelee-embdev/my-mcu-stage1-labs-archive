#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "motor.h"
#include "bluetooth.h"
#include "speed.h"
#include "oled.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    LedInit();
    uart1_init(115200);  
    motor_init();
    bluetooth_init(115200);
    speed_init();
    oled_init();
    printf("Hello World!\n");
  
    motor_go_forward();
    while(1)
    {
        
    }
} 
