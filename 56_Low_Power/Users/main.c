#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "lpwr.h"
#include "key.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    LedInit();
    uart1_init(115200);
    lpwr_init();
    KeyInit();
    printf("Hello World!\n");
    
    uint8_t i =0;
    while(1)
    {
        if(KeyScan() == 2)
        {
//            lpwr_enter_sleep_mode();
//            lpwr_enter_stop_mode();
            lpwr_enter_standby_mode();
        }
        
        if((i %20) == 0)
            Led1Toggle();
        i++;
        delay_ms(10);
    }
}
