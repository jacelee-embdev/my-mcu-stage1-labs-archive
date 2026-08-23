#include "sys.h"
#include "delay.h"
#include "led.h"
#include "pwm_led.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    LedInit();
    pwm_init(500-1,72-1);
    
    int i = 0;
    while(1)
    { 
        for(i = 0; i < 300; i++)
        {
            set_pwm_compare(i);
            delay_ms(10);
        }
        
        for(i = 300; i > 0; i--)
        {
            set_pwm_compare(i);
            delay_ms(10);
        }
    }
}
