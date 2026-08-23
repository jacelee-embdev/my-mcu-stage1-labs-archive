#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "4G_e840.h"
#include "string.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    LedInit();
    uart1_init(115200);
    e840_init(115200);
    printf("Hello World!\n");

    char recv_data[E840_RX_BUF_SIZE];
    while(1)
    {
        e840_receive_data(recv_data);
        if(strstr(recv_data, "ON") != NULL)
        {
           Led1_ON();
        }
        else if(strstr(recv_data, "OFF") != NULL)
        {
            Led1_OFF();
        }
//        Led1_ON();
//        Led2_OFF();
        delay_ms(500);
//        Led1_OFF();
//        Led2_ON();
//        delay_ms(500);
    }
}
