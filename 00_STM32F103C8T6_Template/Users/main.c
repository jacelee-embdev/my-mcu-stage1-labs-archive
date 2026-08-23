#include "sys.h"
#include "delay.h"
#include "uart1.h"
#include "led.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    SystemClock_Config(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    uart1_init(115200);
    led_init();
    
    while(1)
    {
        led_toggle();
        printf("1142!\r\n");
        delay_ms(1000);
    }
}
