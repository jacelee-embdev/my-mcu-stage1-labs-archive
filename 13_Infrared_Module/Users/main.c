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
        if(get_infrared_flag()==TRUE)
        {
            Led1_ON();
            delay_ms(2000);
            Led1_OFF();
            set_infrared_flag(FALSE);
        }
    }
}
