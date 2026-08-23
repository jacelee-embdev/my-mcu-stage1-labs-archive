#include "sys.h"
#include "delay.h"
#include "led.h"
#include "lcd1602.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    LedInit();
    lcd1602_init();
    //lcd1602_show_char(0x80,0x02,'y');
    lcd1602_show_char_string(1,2,"LiZhiQiu");
    lcd1602_show_char_string(2,2,"Handsom");
    
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
