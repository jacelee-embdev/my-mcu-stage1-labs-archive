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
    
    mpu6050_test();
    while(1)
    {
        led_toggle();
//        printf("1142!\r\n");
        delay_ms(1000);
    }
}
