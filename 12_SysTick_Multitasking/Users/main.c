#include "sys.h"
#include "delay.h"
#include "tasks.h"
#include "led.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    LedInit();
    
    while(1)
    { 
        task1();
        task2();
    }
}
