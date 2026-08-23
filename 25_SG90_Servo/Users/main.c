#include "sys.h"
#include "delay.h"
#include "led.h"
#include "pwm_sg90.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    LedInit();
    sg90_init();
    
    while(1)
    { 
        set_sg90_angle(0);
        delay_ms(1000);
        set_sg90_angle(20);
        delay_ms(1000);
        set_sg90_angle(40);
        delay_ms(1000);
        set_sg90_angle(90);
        delay_ms(1000);
        set_sg90_angle(180);
        delay_ms(1000);
    }
}
