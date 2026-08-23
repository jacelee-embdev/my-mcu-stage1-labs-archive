#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "adc.h"

uint16_t adc_result = 0;

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    LedInit();
    uart1_init(115200);
    adc_dma_init((uint32_t *)&adc_result);
    printf("Hello World!\n");
  
    while(1)
    {
        printf("adc result:%fV\r\n",(float)adc_result/4096*3.3);
        Led1_ON();
        Led2_OFF();
        delay_ms(500);
        Led1_OFF();
        Led2_ON();
        delay_ms(500);
    }
}
