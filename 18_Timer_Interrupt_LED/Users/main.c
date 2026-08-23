#include "sys.h"
#include "delay.h"
#include "led.h"
#include "timer.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    LedInit();
    timer_init(5000-1,7200-1);
    
    while(1)
    { 
//        Led1_ON();
//        Led2_OFF();
//        delay_ms(500);
//        Led1_OFF();
//        Led2_ON();
//        delay_ms(500);
    }
}
