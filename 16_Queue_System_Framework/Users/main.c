#include "sys.h"
#include "delay.h"
#include "tasks.h"
#include "led.h"
#include "beep.h"
#include "relay_gate.h"
#include "exti.h"
#include "lcd1602.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    LedInit();
    BeepInit();
    relay_gate_init();
    exti_init();
    lcd1602_init();
    
    lcd1602_show_char_string(1,2,"LiZhiQiu");
    lcd1602_show_char_string(2,2,"Handsom");
    while(1)
    {
        
//        if(get_infrared_status() == 0)
//        {
//            Led1_ON();
//            delay_ms(500);
//            Led1_OFF();
//        }
        
//        Led1_ON();
//        Led2_OFF();
//        Beep_ON();
//        relay_gate_ON();
//        delay_ms(500);
//        
//        Led1_OFF();
//        Led2_ON();
//        Beep_OFF();
//        relay_gate_OFF();
//        delay_ms(500);
        
//        led1_task();
//        led2_task();
        task1();
        task2();
    }
}
