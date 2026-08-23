#include "sys.h"
#include "delay.h"
#include "debug_usart.h"
#include "led.h"
#include "mpu6050.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    SystemClock_Config(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    debug_usart_init(115200);
    led_init();
    mpu6050_init();
    
    while(1)
    {
        mpu6050_test_print_loop();
        led_toggle();
        delay_ms(1000);
//        printf("1142!\r\n");
    }
}
