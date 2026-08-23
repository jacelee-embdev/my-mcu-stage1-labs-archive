#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "bluetooth.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    LedInit();
    uart1_init(115200);
    bluetooth_init(115200);
    printf("Hello World!\n");

    uint8_t i = 0; 
    while(1)
    {
        bluetooh_send("test %d\n",i);
        i++;
        delay_ms(1000);
    }
}
