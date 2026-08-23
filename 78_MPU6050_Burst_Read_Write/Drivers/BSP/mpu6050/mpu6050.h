/**
 * @file    mpu6050.h
 * @brief   MPU6050 六轴加速度计与陀螺仪传感器驱动头文件
 */

#ifndef __MPU6050_H__
#define __MPU6050_H__

#include "sys.h"

/* ================================================================================= */
/* [硬件移植区]                                                                      */
/* ================================================================================= */

/* I2C 物理引脚定义 */
#define MPU6050_IIC_SCL_PORT            GPIOB
#define MPU6050_IIC_SCL_PIN             GPIO_PIN_8
#define MPU6050_IIC_SCL_CLK_EN()        __HAL_RCC_GPIOB_CLK_ENABLE()

#define MPU6050_IIC_SDA_PORT            GPIOB
#define MPU6050_IIC_SDA_PIN             GPIO_PIN_9
#define MPU6050_IIC_SDA_CLK_EN()        __HAL_RCC_GPIOB_CLK_ENABLE()

/* 底层总线电平控制宏 */
#define MPU6050_SCL_H()                 HAL_GPIO_WritePin(MPU6050_IIC_SCL_PORT, MPU6050_IIC_SCL_PIN, GPIO_PIN_SET)
#define MPU6050_SCL_L()                 HAL_GPIO_WritePin(MPU6050_IIC_SCL_PORT, MPU6050_IIC_SCL_PIN, GPIO_PIN_RESET)

#define MPU6050_SDA_H()                 HAL_GPIO_WritePin(MPU6050_IIC_SDA_PORT, MPU6050_IIC_SDA_PIN, GPIO_PIN_SET)
#define MPU6050_SDA_L()                 HAL_GPIO_WritePin(MPU6050_IIC_SDA_PORT, MPU6050_IIC_SDA_PIN, GPIO_PIN_RESET)

#define MPU6050_SDA_READ()              HAL_GPIO_ReadPin(MPU6050_IIC_SDA_PORT, MPU6050_IIC_SDA_PIN)

/* ================================================================================= */
/* [配置参数区]                                                                      */
/* ================================================================================= */

/* 器件基础配置 */
#define MPU6050_DEVICE_ADDR             0x68    // 从机 7 位地址 (AD0 接地)
#define MPU6050_IIC_TIMEOUT             2000    // 模拟 I2C 等待应答超时阈值

/* MPU6050 核心寄存器映射 */
#define MPU6050_SMPLRT_DIV              0x19    // 采样率分频
#define MPU6050_CONFIG                  0x1A    // 数字低通滤波器配置
#define MPU6050_GYRO_CONFIG             0x1B    // 陀螺仪量程配置
#define MPU6050_ACCEL_CONFIG            0x1C    // 加速度计量程配置
    
#define MPU6050_ACCEL_XOUT_H            0x3B    // 传感器数据起始地址 (Accel_X_H)
#define MPU6050_PWR_MGMT_1              0x6B    // 电源管理 1
#define MPU6050_PWR_MGMT_2              0x6C    // 电源管理 2
#define MPU6050_WHO_AM_I                0x75    // 器件 ID 寄存器

/* ================================================================================= */
/* [功能接口声明]                                                                    */
/* ================================================================================= */

/**
 * @brief  初始化 MPU6050 硬件配置并检查器件连接状态
 * @return 0: 正常; 1: 器件异常或连接失败
 */
uint8_t mpu6050_init(void);

/**
 * @brief  向 MPU6050 连续写入数据缓冲区 (突发写)
 * @param  reg_start_addr: 寄存器起始地址
 * @param  buffer_size:    待写入的字节总数
 * @param  p_source_buf:   指向待发送数据源的指针
 */
void mpu6050_burst_write(uint8_t reg_start_addr, uint8_t buffer_size, uint8_t *p_source_buf);

/**
 * @brief  从 MPU6050 连续读取数据到缓冲区 (突发读)
 * @param  reg_start_addr: 寄存器起始地址
 * @param  buffer_size:    待读取的字节总数
 * @param  p_dest_buf:     指向目标接收缓冲区的指针
 */
void mpu6050_burst_read(uint8_t reg_start_addr, uint8_t buffer_size, uint8_t *p_dest_buf);

/**
 * @brief  执行 MPU6050 通讯链路与寄存器读写诊断测试
 */
void mpu6050_test(void);

#endif /* __MPU6050_H__ */
