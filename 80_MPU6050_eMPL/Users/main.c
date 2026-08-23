/**
 * @file    main.c
 * @brief   主程序入口：完成系统初始化与 MPU6050 姿态解算轮询调度
 */

#include "sys.h"
#include "delay.h"
#include "debug_usart.h"
#include "led.h"
#include "mpu6050.h"

// 系统主程序：完成外设初始化与 MPU6050 姿态解算轮询
int main(void)
{
    /* 阶段 1: 系统底层与外设初始化 */
    HAL_Init();                                 // 初始化 HAL 库
    SystemClock_Config(RCC_PLL_MUL9);           // 配置时钟树: 72MHz 系统主频
    debug_usart_init(115200);                   // 初始化串口: 115200bps，用于调试打印
    led_init();                                 // 初始化 LED:  用作系统心跳指示
    mpu6050_init();                             // 唤醒 MPU6050 并挂载 DMP 固件
    
    /* 阶段 2: 业务数据栈初始化 */
    float    pitch        = 0.0f;               // 俯仰角缓冲
    float    roll         = 0.0f;               // 横滚角缓冲
    float    yaw          = 0.0f;               // 偏航角缓冲
    uint16_t task_counter = 0;                  // 串口输出降频计数器
    
    /* 阶段 3: 核心业务轮询 */
    while(1)
    {
        /* 步骤 1: 非阻塞拉取 DMP 姿态数据 (返回 0 表示有效) */
        if (mpu6050_dmp_get_data(&pitch, &roll, &yaw) == 0)
        {
            task_counter++;
            
            /* 步骤 2: 降频输出外设状态 (DMP 速率约 100Hz，累计 100 次即 1 秒) */
            if (task_counter >= 100) 
            {
                printf("pitch: %.2f roll: %.2f yaw: %.2f\r\n", pitch, roll, yaw);
                led_toggle();                   // 翻转心跳灯，指示系统正常运行
                task_counter = 0;
            }
        }
        
        /* 步骤 3: 维持 5ms 轮询节拍，及时清空数据防止 MPU6050 FIFO 溢出 */
        delay_ms(5); 
    }
}
