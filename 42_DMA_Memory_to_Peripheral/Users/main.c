#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "dma.h"

extern UART_HandleTypeDef uart1_handle;

uint8_t send_buf[1000] = {0};

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    LedInit();
    uart1_init(115200);
    dam_init();
//    printf("Hello World!\r\n");
    
    int i=0;
    for(i=0;i<1000;i++)
    {
        send_buf[i]= 'A';
    }
    
   HAL_UART_Transmit_DMA(&uart1_handle,send_buf,1000);
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
