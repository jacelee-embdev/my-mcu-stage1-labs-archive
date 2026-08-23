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
        if(get_buttonB_flag()==TRUE)
        {
            Led2Toggle();
        }
        
        if(get_buttonA_flag()==TRUE)
        {
            Led1Toggle();
        }
    }
}
