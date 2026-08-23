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
  
    
    
    if(rtc_read_bkr(1) != 0xA5A5)
    {
        rtc_write_bkr(1,0xA5A5);
        printf("读出的值为:%X\r\n",rtc_read_bkr(1));
        
        struct tm time_data;
        time_data.tm_year   = 2026;
        time_data.tm_mon    = 1;
        time_data.tm_mday   = 24;
        time_data.tm_hour   = 21;
        time_data.tm_min    = 40;
        time_data.tm_sec    = 5;
        rtc_set_time(time_data);
    }
    
    while(1)
    {
        rtc_get_time();
        Led1_ON();
        Led2_OFF();
        delay_ms(500);
        Led1_OFF();
        Led2_ON();
        delay_ms(500);
    }
}
