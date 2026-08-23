#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "keyboard.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9);     /* 设置时钟, 72Mhz */
    LedInit();                         /* 初始化LED灯 */
    uart1_init(115200);                 /* 初始化串口 */
    keyboard_init();
    printf("Hello Word!");
    
    uint8_t key_val = 0;
    
    while(1)
    { 
        // 从全局缓冲区获取键值
        key_val = keyboard_get_value();
        
        if(key_val != 0)
        {
            printf("按下了：%c\r\n", key_val);
            
            Led1_ON();
            delay_ms(50);
            Led1_OFF();
        }
        delay_ms(10);
    }
}
