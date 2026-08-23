#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "iwdg.h"


int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    LedInit();
    uart1_init(115200);
    iwdg_init(IWDG_PRESCALER_64,625);
    printf("Hello World!\n");
  
    printf("需要喂狗！\r\n");
    
    if(__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST) != RESET)
    {
        printf("独立看门狗复位!\r\n");
        __HAL_RCC_CLEAR_RESET_FLAGS();
    }
    else
        printf("外部复位!\r\n");
    
    while(1)
    {
        iwdg_test();
        delay_ms(100);
        iwdg_feed();
        printf("喂狗成功!\n");
        
//        printf("TEST1\n");
//        delay_ms(3000);
//        printf("TEST2\n");
////        Led1_ON();
////        Led2_OFF();
////        delay_ms(500);
////        Led1_OFF();
////        Led2_ON();
////        delay_ms(500);
    }
}
