#include "sys.h"
#include "delay.h"
#include "debug_usart.h"
#include "led.h"
#include "encoder.h"


int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    SystemClock_Config(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    debug_usart_init(115200);
    led_init();
    encoder_init();
    
    int16_t count = 0;
    while(1)
    {
        count = encoder_get_count_delta();
        printf("COUNT:%d\r\n",count);
        led_toggle();
//        printf("1142!\r\n");
        delay_ms(1000);
    }
}
