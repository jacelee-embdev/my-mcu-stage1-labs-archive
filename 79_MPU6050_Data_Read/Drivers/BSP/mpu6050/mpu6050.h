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
#define MPU6050_DEVICE_ADDR             0x68    // 从机 7 位地址 (AD0 默认接地)
#define MPU6050_IIC_TIMEOUT             2000    // 模拟 I2C 等待应答超时阈值，防止总线死锁

/* MPU6050 核心寄存器映射 */
#define MPU6050_SMPLRT_DIV              0x19    // 采样率分频寄存器
#define MPU6050_CONFIG                  0x1A    // 综合配置寄存器 (数字低通滤波器 DLPF)
#define MPU6050_GYRO_CONFIG             0x1B    // 陀螺仪量程配置寄存器
#define MPU6050_ACCEL_CONFIG            0x1C    // 加速度计量程配置寄存器
    
#define MPU6050_ACCEL_XOUT_H            0x3B    // 加速度计 X 轴高位寄存器 (突发读取起始地址)
#define MPU6050_ACCEL_XOUT_L            0x3C    // 加速度计 X 轴低位寄存器
#define MPU6050_ACCEL_YOUT_H            0x3D    // 加速度计 Y 轴高位寄存器
#define MPU6050_ACCEL_YOUT_L            0x3E    // 加速度计 Y 轴低位寄存器
#define MPU6050_ACCEL_ZOUT_H            0x3F    // 加速度计 Z 轴高位寄存器
#define MPU6050_ACCEL_ZOUT_L            0x40    // 加速度计 Z 轴低位寄存器

#define MPU6050_TEMP_OUT_H              0x41    // 温度传感器高位寄存器
#define MPU6050_TEMP_OUT_L              0x42    // 温度传感器低位寄存器

#define MPU6050_GYRO_XOUT_H             0x43    // 陀螺仪 X 轴高位寄存器
#define MPU6050_GYRO_XOUT_L             0x44    // 陀螺仪 X 轴低位寄存器
#define MPU6050_GYRO_YOUT_H             0x45    // 陀螺仪 Y 轴高位寄存器
#define MPU6050_GYRO_YOUT_L             0x46    // 陀螺仪 Y 轴低位寄存器
#define MPU6050_GYRO_ZOUT_H             0x47    // 陀螺仪 Z 轴高位寄存器
#define MPU6050_GYRO_ZOUT_L             0x48    // 陀螺仪 Z 轴低位寄存器
    
#define MPU6050_PWR_MGMT_1              0x6B    // 电源管理寄存器 1 (设备复位、时钟源选择)
#define MPU6050_PWR_MGMT_2              0x6C    // 电源管理寄存器 2 (休眠控制)
#define MPU6050_WHO_AM_I                0x75    // 器件 ID 寄存器 (默认验证值 0x68)

/* ================================================================================= */
/* [功能接口声明]                                                                    */
/* ================================================================================= */

// 初始化 MPU6050 硬件配置并检查器件连接状态
uint8_t mpu6050_init(void);

// 向 MPU6050 连续写入数据缓冲区 (突发写)
void mpu6050_burst_write(uint8_t reg_start_addr, uint8_t buffer_size, uint8_t *p_source_buf);

// 从 MPU6050 连续读取数据到缓冲区 (突发读)
void mpu6050_burst_read(uint8_t reg_start_addr, uint8_t buffer_size, uint8_t *p_dest_buf);

// 突发读取 MPU6050 加速度计、温度计与陀螺仪原始数据 (共 14 字节)
void mpu6050_read_all_data(int16_t *p_accel_x, int16_t *p_accel_y, int16_t *p_accel_z, int16_t *p_temp, int16_t *p_gyro_x, int16_t *p_gyro_y, int16_t *p_gyro_z);

// MPU6050 全数据采集与串口打印测试
void mpu6050_test_print_loop(void);

#endif /* __MPU6050_H__ */
