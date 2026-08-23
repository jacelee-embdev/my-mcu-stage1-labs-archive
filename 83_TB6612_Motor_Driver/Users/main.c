#include "sys.h"
#include "delay.h"
#include "debug_usart.h"
#include "led.h"
#include "motor.h"


int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    SystemClock_Config(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    debug_usart_init(115200);
    led_init();
    motor_init();
    
    while(1)
    {
//        motor_test_sequence();
        led_toggle();
//        printf("1142!\r\n");

    }
}
