#include "sys.h"
#include "delay.h"
#include "led.h"
#include "exti.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    LedInit();
    exti_init();
    
    
    while(1)
    { 
        Led2_OFF();
        delay_ms(500);
        Led2_ON();
        delay_ms(500);
    }
}
