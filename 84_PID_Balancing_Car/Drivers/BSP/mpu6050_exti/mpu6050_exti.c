#include "mpu6050_exti.h"

/* ================================================================================= */
/* [私有变量与句柄] 跨文件共享状态标志                                               */
/* ================================================================================= */
volatile uint8_t mpu6050_data_ready_flag = 0; // MPU数据就绪标志，由硬件中断触发置1，由主循环消费并清零

/* ================================================================================= */
/* [核心业务接口] 对外暴露的功能实现                                                 */
/* ================================================================================= */

// 配置引脚模式为外部中断，上升沿触发，启用内部上拉保持电平稳定防误触
void mpu6050_exti_init(void)
{
    GPIO_InitTypeDef gpio_initstruct;
    
    /* 阶段 1: 开启GPIO外设时钟 */
    MPU6050_INT_CLK_ENABLE();
    
    /* 阶段 2: 配置EXTI引脚属性 */
    gpio_initstruct.Pin  = MPU6050_INT_PIN;
    gpio_initstruct.Mode = GPIO_MODE_IT_RISING;   
    gpio_initstruct.Pull = GPIO_PULLUP;           
    HAL_GPIO_Init(MPU6050_INT_PORT, &gpio_initstruct);
    
    /* 阶段 3: 配置NVIC中断优先级并使能（抢占优先级2，响应优先级2） */
    HAL_NVIC_SetPriority(MPU6050_INT_IRQn, 2, 2);
    HAL_NVIC_EnableIRQ(MPU6050_INT_IRQn);
}

// EXTI线15-10中断服务函数，硬件级触发入口
void EXTI15_10_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(MPU6050_INT_PIN); // 调用HAL库通用处理链，自动清除挂起寄存器标志位
}

// 外部中断底线回调，通知应用层MPU6050内部DMP姿态解算已完成
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == MPU6050_INT_PIN)
    {
        mpu6050_data_ready_flag = 1; 
    }
}
