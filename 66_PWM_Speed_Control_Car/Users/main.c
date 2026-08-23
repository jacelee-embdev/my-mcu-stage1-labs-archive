#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "motor.h"
#include "pwm.h" 

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    LedInit();
    uart1_init(115200);
    motor_init();
    pwm_init(20-1,72-1);
    printf("Hello World!\n");
  
    while(1)
    {
        set_left_motor_pwm(8);
        set_right_motor_pwm(15);
        delay_ms(1000);
        printf("111"); 
        set_left_motor_pwm(15);
        set_right_motor_pwm(8);
        delay_ms(1000);
        
        set_left_motor_pwm(15);
        set_right_motor_pwm(15);
        delay_ms(1000);
    }
} 
