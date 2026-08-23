#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "dht11.h"
#include "string.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    LedInit();
    uart1_init(115200);
    printf("Hello World!\n");
    
    uint8_t dht11_result[4];
    while(1)
    {
        memset(dht11_result,0,4);
        dht11_read_data(dht11_result);
        Led1_ON();
        Led2_OFF();
        delay_ms(500);
        Led1_OFF();
        Led2_ON();
        delay_ms(500);
    }
}
