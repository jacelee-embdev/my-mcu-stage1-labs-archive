#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "bluetooth.h"
#include "relay_plugin.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    LedInit();
    uart1_init(115200);
    bluetooth_init(115200);
    relay_plugin_init();
    printf("Hello World!\n");

    while(1)
    {
        delay_ms(1000);
    }
}
