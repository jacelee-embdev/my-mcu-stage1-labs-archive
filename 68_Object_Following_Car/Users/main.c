#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "motor.h"
#include "follow.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    LedInit();
    uart1_init(115200);
    motor_init();
    follow_init();
    printf("Hello World!\n");
  
    while(1)
    {
        if(get_left_follow_flag() == TRUE && get_right_follow_flag() == TRUE)
        {
            motor_go_forward();
        }
        else if(get_left_follow_flag() == FALSE && get_right_follow_flag() == TRUE)
        {
            motor_go_right(); 
        }
        else if(get_left_follow_flag() == TRUE && get_right_follow_flag() == FALSE)
        {
            motor_go_left();
        }
        else if(get_left_follow_flag() == FALSE && get_right_follow_flag() == FALSE)
        {
            motor_stop();
        }
    }
} 
