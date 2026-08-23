/**
 * @file    main.c
 */

#include "sys.h"
#include "delay.h"
#include "debug_usart.h"
#include "led.h"
#include "mpu6050.h"
#include "control.h"
#include "encoder.h"
#include "motor.h"
#include "bluetooth.h"
#include "mpu6050_exti.h"

int main(void)
{
    HAL_Init();                                 // 初始化 HAL 库
    SystemClock_Config(RCC_PLL_MUL9);           // 配置时钟树: 72MHz 系统主频
    debug_usart_init(115200);                   // 初始化串口: 115200bps，用于调试打印
    led_init();                                 // 初始化 LED:  用作系统心跳指示
    mpu6050_init();                             // 唤醒 MPU6050 并挂载 DMP 固件
    delay_ms(1000);
    encoder_init();
    motor_init();
    bluetooth_init(115200);
    mpu6050_exti_init();
    
//    uint8_t bt_cmd = 0;
    while(1)
    {
//        bt_cmd = bluetooth_get_command();
//        printf("bt_cmd:%d\r\n",bt_cmd);
//        delay_ms(1000);
        control_task_loop();
    }
}
