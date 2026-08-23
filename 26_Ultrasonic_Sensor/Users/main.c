#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "hcsr04.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    LedInit();
    uart1_init(115200);
    hcsr04_init();
    printf("Hello World!\n");
  
    while(1)
    {
        printf("distance:%.2f\r\n ",get_length_from_hcsr04());
        delay_ms(1000);
    }
}
