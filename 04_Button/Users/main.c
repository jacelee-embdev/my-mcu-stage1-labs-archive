#include "sys.h"
#include "delay.h"
#include "led.h"
#include "key.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    LedInit();
    KeyInit();
    
    uint8_t key_nub=0;
    while(1)
    { 
        key_nub=KeyScan();
        
        if(key_nub==1)
        {
            Led1Toggle();
        }
        
        if(key_nub==2)
        {
            Led2Toggle();
        }
    }
}
