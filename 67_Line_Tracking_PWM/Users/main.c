#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "motor.h"
#include "pwm.h" 
#include "track.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    LedInit();
    uart1_init(115200);
    motor_init();
    pwm_init(200-1,720-1);
    track_init();
    printf("Hello World!\n");
  
    while(1)
    {
        if(get_left_track_flag() == TRUE && get_right_track_flag() == TRUE)
        {
            set_left_motor_pwm(95);
            set_right_motor_pwm(95);
        }
        else if(get_left_track_flag() == FALSE && get_right_track_flag() == TRUE)
        {
            set_left_motor_pwm(0);
            set_right_motor_pwm(95);
        }
        else if(get_left_track_flag() == TRUE && get_right_track_flag() == FALSE)
        {
            set_left_motor_pwm(95);
            set_right_motor_pwm(0);
        }
        else if(get_left_track_flag() == FALSE && get_right_track_flag() == FALSE)
        {
            set_left_motor_pwm(0);
            set_right_motor_pwm(0);
        }
        
        delay_ms(10);
    }
} 
