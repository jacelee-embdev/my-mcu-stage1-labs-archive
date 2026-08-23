#include "sys.h"
#include "delay.h"
#include "relay_alarm.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    relay_alarm_init();

    
    while(1)
    { 
        relay_alarm_ON();
        delay_ms(200);
        relay_alarm_OFF();
        delay_ms(200);
    }
}
