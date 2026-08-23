#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "adc.h"
#include "beep.h"
#include "key.h"
#include "lcd1602.h"
#include "relay_fan.h"

int main(void)
{
    float now_smoke_value =0;
    float limit_value = 1.0;
    uint8_t key_num;
    
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    LedInit();
    uart1_init(115200);
    adc_dma_init();
    BeepInit();
    KeyInit();
    lcd1602_init();
    relay_fan_init();
    
    printf("Hello World!\n");
    
    while(1)
    {
        key_num = KeyScan();
        if(key_num == 1)
        {
            limit_value -=0.1;
        }
        else if(key_num == 2)
        {
            limit_value += 0.1;
        }
        
        lcd1602_display_limit(limit_value);
        
        now_smoke_value = get_adc_value();
        lcd1602_display_smoke(now_smoke_value);
        
        if(now_smoke_value > limit_value)
        {
            relay_fan_ON();
            Beep_ON();
        }
        else
        {
            relay_fan_OFF();
            Beep_OFF();
        }
    }
}
