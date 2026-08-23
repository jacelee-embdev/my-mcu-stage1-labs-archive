#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "can.h"
#include "key.h"

uint8_t data_send[8] = {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88};
uint8_t data_receive[8];
int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    LedInit();
    uart1_init(115200);
    KeyInit();
    can_init();
    printf("Hello World!\n");
    
    uint8_t i = 0;
    while(1)
    {
        if(KeyScan() == 1)
        {
            for(i =0; i < 8;i++)
            { 
                data_send[i]++;
            }
            can_send_data(0x12345678,data_send,8);
        }
        can_receive_data(data_receive);
        
        Led1_ON();
        Led2_OFF();
        delay_ms(500);
        Led1_OFF();
        Led2_ON();
        delay_ms(500);
    }
}
