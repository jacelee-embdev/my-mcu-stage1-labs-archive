#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "counter.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    LedInit();
    uart1_init(115200);
    counter_init(65536-1,0);
    printf("Hello World!\n");
  
    while(1)
    { 
        get_count();
    }
}
