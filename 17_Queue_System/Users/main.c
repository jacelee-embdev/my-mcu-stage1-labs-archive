#include "sys.h"
#include "delay.h"
#include "tasks.h"
#include "led.h"
#include "beep.h"
#include "relay_gate.h"
#include "exti.h"
#include "lcd1602.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    LedInit();
    BeepInit();
    relay_gate_init();
    exti_init();
    lcd1602_init();
    
    lcd1602_show_char_string(1,2,"PASS...");
    while(1)         // 无限循环：模拟多线程调度，通过轮询方式依次执行各功能任务，无退出条件
    {
        led1_task();
        led2_task();
        alarm_bee_task();
        lcd1602_task();
    }
}
