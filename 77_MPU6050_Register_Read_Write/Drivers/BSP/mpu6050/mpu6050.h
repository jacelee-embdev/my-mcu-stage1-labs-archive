#ifndef __MPU6050_H__
#define __MPU6050_H__

#include "sys.h"

/* --- 引脚配置区 --- */
#define MPU6050_IIC_SCL_PORT       GPIOB
#define MPU6050_IIC_SCL_PIN        GPIO_PIN_8
#define MPU6050_IIC_SCL_CLK_EN()   __HAL_RCC_GPIOB_CLK_ENABLE()

#define MPU6050_IIC_SDA_PORT       GPIOB
#define MPU6050_IIC_SDA_PIN        GPIO_PIN_9
#define MPU6050_IIC_SDA_CLK_EN()   __HAL_RCC_GPIOB_CLK_ENABLE()

/* --- I2C 总线控制宏 --- */
#define MPU6050_SCL_H()    HAL_GPIO_WritePin(MPU6050_IIC_SCL_PORT, MPU6050_IIC_SCL_PIN, GPIO_PIN_SET)
#define MPU6050_SCL_L()    HAL_GPIO_WritePin(MPU6050_IIC_SCL_PORT, MPU6050_IIC_SCL_PIN, GPIO_PIN_RESET)

#define MPU6050_SDA_H()    HAL_GPIO_WritePin(MPU6050_IIC_SDA_PORT, MPU6050_IIC_SDA_PIN, GPIO_PIN_SET)
#define MPU6050_SDA_L()    HAL_GPIO_WritePin(MPU6050_IIC_SDA_PORT, MPU6050_IIC_SDA_PIN, GPIO_PIN_RESET)

#define MPU6050_SDA_READ() HAL_GPIO_ReadPin(MPU6050_IIC_SDA_PORT, MPU6050_IIC_SDA_PIN)

/* --- 设备地址 --- */
#define MPU6050_ADDRESS    0x68

/* --- 函数声明 --- */
void mpu6050_init(void);
void mpu6050_test(void);

#endif
