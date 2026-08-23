#include "sys.h"
#include "delay.h"
#include "beep.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    BeepInit();
    
    while(1)
    { 
        Beep_ON();
        delay_ms(500);
        Beep_OFF();
        delay_ms(500);
    }
}
