#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "rtc.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    LedInit();
    uart1_init(115200);
    rtc_init();
    printf("Hello World!\n");
  
    rtc_write_bkr(1,0xA5A5);
    printf("读出的值为:%X\r\n",rtc_read_bkr(1));
    
    while(1)
    {
        Led1_ON();
        Led2_OFF();
        delay_ms(500);
        Led1_OFF();
        Led2_ON();
        delay_ms(500);
    }
}
