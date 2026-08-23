/**
 * @file    main.c
 */

#include "sys.h"
#include "delay.h"
#include "debug_usart.h"
#include "led.h"
#include "mpu6050.h"
#include "control.h"

int main(void)
{
    HAL_Init();                                 // 初始化 HAL 库
    SystemClock_Config(RCC_PLL_MUL9);           // 配置时钟树: 72MHz 系统主频
    debug_usart_init(115200);                   // 初始化串口: 115200bps，用于调试打印
    led_init();                                 // 初始化 LED:  用作系统心跳指示
    mpu6050_init();                             // 唤醒 MPU6050 并挂载 DMP 固件
    control_init();
    
    
    while(1)
    {
        led_toggle();
        delay_ms(500); 
        printf("1142!\r\n");
    }
}
