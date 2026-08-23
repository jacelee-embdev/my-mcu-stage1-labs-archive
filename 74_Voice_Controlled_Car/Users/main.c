#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "motor.h"
#include "follow.h"
#include "hcsr04.h"
#include "pwm_sg90.h"
#include "track.h"
#include "voice_control.h"

    double dis_left = 0;
    double dis_middle = 0;
    double dis_right = 0;

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    LedInit();
    uart1_init(115200);
    motor_init();
    follow_init();
    hcsr04_init();
    sg90_init();
    track_init();
    voice_control_init();
    
    printf("Hello World!\n");
  
    while(1)
    {
        if(PIN_1 == GPIO_PIN_RESET && PIN_2 == GPIO_PIN_RESET && PIN_3 == GPIO_PIN_SET)
            printf("001\r\n");
        else if(PIN_1 == GPIO_PIN_RESET && PIN_2 == GPIO_PIN_SET && PIN_3 == GPIO_PIN_RESET)
            printf("010\r\n");
        else if(PIN_1 == GPIO_PIN_RESET && PIN_2 == GPIO_PIN_SET && PIN_3 == GPIO_PIN_SET)
            printf("011\r\n");
        else if(PIN_1 == GPIO_PIN_SET && PIN_2 == GPIO_PIN_RESET && PIN_3 == GPIO_PIN_RESET)
            printf("100\r\n");
        else if(PIN_1 == GPIO_PIN_SET && PIN_2 == GPIO_PIN_RESET && PIN_3 == GPIO_PIN_SET)
            printf("101");
        else if(PIN_1 == GPIO_PIN_SET && PIN_2 == GPIO_PIN_SET && PIN_3 == GPIO_PIN_RESET)
            printf("110\r\n");
        
        delay_ms(1000);
    }
} 

void track_mode(void)
{
    if(get_left_track_flag() == TRUE && get_right_track_flag() == TRUE)
    {
        motor_go_forward();
    }
    else if(get_left_track_flag() == FALSE && get_right_track_flag() == TRUE)
    {
        motor_go_left();
    }
    else if(get_left_track_flag() == TRUE && get_right_track_flag() == FALSE)
    {
        motor_go_right();
    }
    else if(get_left_track_flag() == FALSE && get_right_track_flag() == FALSE)
    {
        motor_stop();
    }
    
    delay_ms(10);
}

void follow_mode(void)
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

    
void avoidance_mode(void)
{
    motor_stop();
    
    sg90_turn_middle();
    
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
