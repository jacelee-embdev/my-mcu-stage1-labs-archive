#include "sys.h"
#include "delay.h"
#include "led.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    LedInit();
//    Led_ON();
    
    while(1)
    { 
        LedToggle();
        delay_ms(500);
    }
}
