#include "control.h"
#include "debug_usart.h"
#include "mpu6050.h"

/* ================================================================================= */
/* [私有变量与句柄] 模块内部私有数据，严格限制作用域防污染                           */
/* ================================================================================= */
static float pitch;                             // DMP 解算后俯仰角数据缓冲区
static float roll;                              // DMP 解算后横滚角数据缓冲区
static float yaw;                               // DMP 解算后航向角数据缓冲区

/* ================================================================================= */
/* [应用层] 核心业务接口                                                             */
/* ================================================================================= */

/*
 * @brief   初始化控制模块底层硬件（外置 MPU6050 中断引脚配置）
 */
void control_init(void)
{
    GPIO_InitTypeDef gpio_initstruct;
    
    /* 阶段 1: 使能中断引脚所在 GPIO 端口的外设时钟 */
    MPU_INT_CLK_ENABLE();
    
    /* 阶段 2: 配置引脚模式为外部中断，上升沿触发，启用内部上拉电阻保持电平稳定 */
    gpio_initstruct.Pin  = MPU_INT_PIN;
    gpio_initstruct.Mode = GPIO_MODE_IT_RISING;   
    gpio_initstruct.Pull = GPIO_PULLUP;           
    HAL_GPIO_Init(MPU_INT_PORT, &gpio_initstruct);
    
    /* 阶段 3: 配置 EXTI 线中断优先级并使能通道（抢占优先级2，响应优先级2） */
    HAL_NVIC_SetPriority(MPU_INT_IRQn, 2, 2);
    HAL_NVIC_EnableIRQ(MPU_INT_IRQn);
}

/* ================================================================================= */
/* [物理层/逻辑处理层] 中断服务与底层回调机制                                        */
/* ================================================================================= */

/*
 * @brief   EXTI 线 15-10 中断服务函数
 */
void EXTI15_10_IRQHandler(void)
{
    // 调用 HAL 库公共 EXTI 处理函数，自动清除挂起标志位并触发回调
    HAL_GPIO_EXTI_IRQHandler(MPU_INT_PIN);
}

/*
 * @brief   GPIO 外部中断回调函数，处理 MPU6050 姿态数据就绪事件
 * @param   GPIO_Pin: 触发当前中断的引脚编号
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    static uint8_t s_print_counter = 0;
    
    if (GPIO_Pin == MPU_INT_PIN)
    {
        // 突发读取 DMP 解算的最新姿态欧拉角并存入私有缓冲区
        mpu6050_dmp_get_data(&pitch, &roll, &yaw);
        
        // 利用软计数器对串口打印速率进行分频，避免频繁 I/O 阻塞中断上下文
        if (s_print_counter == MPU_PRINT_FREQ_DIV)
        {
            printf("pitch: %f roll:%f yaw:%f\r\n", pitch, roll, yaw);
            s_print_counter = 0;
        }
        s_print_counter++;
    }
}
