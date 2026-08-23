#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "motor.h"
#include "bluetooth.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    LedInit();
    uart1_init(115200);
    motor_init();
    bluetooth_init(115200);
    printf("Hello World!\n");
  
    while(1)
    {
//        motor_go_forward();
//        delay_ms(1000);
//        motor_go_backward();
//        delay_ms(1000);
//        motor_go_left();
//        delay_ms(1000);
//        motor_go_right();
//        delay_ms(1000);
//        motor_stop();
//        delay_ms(1000);
    }
} 
