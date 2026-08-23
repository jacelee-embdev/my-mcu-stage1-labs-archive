#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "motor.h"
#include "pwm_sg90.h" 
#include "hcsr04.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    LedInit();
    uart1_init(115200);
    motor_init();
    sg90_init();
    hcsr04_init();
    printf("Hello World!\n");
  
    double dis_left = 0;
    double dis_middle = 0;
    double dis_right = 0;
    
    while(1)
    {
        printf("DIS:%.2f\r\n",get_length_from_hcsr04());
        motor_stop();
            
            //向左看并测量左侧距离
            sg90_turn_left();
            delay_ms(500);
            dis_left = get_length_from_hcsr04();
            
            //居中
            sg90_turn_middle();
            delay_ms(500);
            
            //向右看并测量右侧距离
            sg90_turn_right();
            delay_ms(500);
            dis_right = get_length_from_hcsr04();
            
            //根据距离判断左转还是右转
            if(dis_left < dis_right)
                motor_go_right();
            else
                motor_go_left();
            
            delay_ms(200);
            motor_stop();
            sg90_turn_middle();
    }
} 
