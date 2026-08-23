/**
 * @file    mpu6050.h
 * @brief   MPU6050 六轴加速度计与陀螺仪传感器驱动头文件
 */

#ifndef __MPU6050_H__
#define __MPU6050_H__

#include "sys.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include <math.h>

/* ================================================================================= */
/* [硬件移植区] 集中放置底层硬件相关的宏定义，便于跨平台移植                         */
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
/* [配置参数区] 软件逻辑相关的参数阈值                                               */
/* ================================================================================= */

#define Q30_FORMAT_DIVISOR              1073741824.0f   // Q30 格式定点数转浮点数除数

/* 器件基础配置 */
#define MPU6050_DEVICE_ADDR             0x68            // 从机 7 位地址 (AD0 默认接地)
#define MPU6050_IIC_TIMEOUT             2000            // 模拟 I2C 等待应答超时阈值

/* 读写地址(8位)，用于某些特定驱动库 */
#define MPU6050_READ_ADDR               0xD1            // 器件读地址
#define MPU6050_WRITE_ADDR              0xD0            // 器件写地址

/* ================================================================================= */
/* [MPU6050 寄存器映射] 物理寄存器地址定义                                           */
/* ================================================================================= */

/* 自检寄存器 */
#define MPU6050_SELF_TEST_X             0x0D
#define MPU6050_SELF_TEST_Y             0x0E
#define MPU6050_SELF_TEST_Z             0x0F
#define MPU6050_SELF_TEST_A             0x10

/* 配置寄存器 */
#define MPU6050_SMPLRT_DIV              0x19            // 采样率分频寄存器
#define MPU6050_CONFIG                  0x1A            // 综合配置寄存器 (DLPF)
#define MPU6050_GYRO_CONFIG             0x1B            // 陀螺仪量程配置寄存器
#define MPU6050_ACCEL_CONFIG            0x1C            // 加速度计量程配置寄存器
#define MPU6050_MOTION_DET_THR          0x1F            // 运动检测阈值

/* FIFO 与 I2C 主机控制 */
#define MPU6050_FIFO_EN                 0x23            // FIFO 使能
#define MPU6050_I2C_MST_CTRL            0x24            // IIC 主机控制
#define MPU6050_I2C_SLV0_ADDR           0x25            // IIC 从机 0 器件地址
#define MPU6050_I2C_SLV0_REG            0x26            // IIC 从机 0 寄存器地址
#define MPU6050_I2C_SLV0_CTRL           0x27            // IIC 从机 0 控制
#define MPU6050_I2C_SLV1_ADDR           0x28            // IIC 从机 1 器件地址
#define MPU6050_I2C_SLV1_REG            0x29            // IIC 从机 1 寄存器地址
#define MPU6050_I2C_SLV1_CTRL           0x2A            // IIC 从机 1 控制
#define MPU6050_I2C_SLV2_ADDR           0x2B            // IIC 从机 2 器件地址
#define MPU6050_I2C_SLV2_REG            0x2C            // IIC 从机 2 寄存器地址
#define MPU6050_I2C_SLV2_CTRL           0x2D            // IIC 从机 2 控制
#define MPU6050_I2C_SLV3_ADDR           0x2E            // IIC 从机 3 器件地址
#define MPU6050_I2C_SLV3_REG            0x2F            // IIC 从机 3 寄存器地址
#define MPU6050_I2C_SLV3_CTRL           0x30            // IIC 从机 3 控制
#define MPU6050_I2C_SLV4_ADDR           0x31            // IIC 从机 4 器件地址
#define MPU6050_I2C_SLV4_REG            0x32            // IIC 从机 4 寄存器地址
#define MPU6050_I2C_SLV4_DO             0x33            // IIC 从机 4 写数据
#define MPU6050_I2C_SLV4_CTRL           0x34            // IIC 从机 4 控制
#define MPU6050_I2C_SLV4_DI             0x35            // IIC 从机 4 读数据
#define MPU6050_I2C_MST_STATUS          0x36            // IIC 主机状态

/* 中断控制 */
#define MPU6050_INT_PIN_CFG             0x37            // 中断/旁路设置
#define MPU6050_INT_ENABLE              0x38            // 中断使能
#define MPU6050_INT_STATUS              0x3A            // 中断状态

/* 加速度计原始数据 */
#define MPU6050_ACCEL_XOUT_H            0x3B            // 加速度计 X 轴高位
#define MPU6050_ACCEL_XOUT_L            0x3C            // 加速度计 X 轴低位
#define MPU6050_ACCEL_YOUT_H            0x3D            // 加速度计 Y 轴高位
#define MPU6050_ACCEL_YOUT_L            0x3E            // 加速度计 Y 轴低位
#define MPU6050_ACCEL_ZOUT_H            0x3F            // 加速度计 Z 轴高位
#define MPU6050_ACCEL_ZOUT_L            0x40            // 加速度计 Z 轴低位

/* 温度传感器数据 */
#define MPU6050_TEMP_OUT_H              0x41            // 温度传感器高位
#define MPU6050_TEMP_OUT_L              0x42            // 温度传感器低位

/* 陀螺仪原始数据 */
#define MPU6050_GYRO_XOUT_H             0x43            // 陀螺仪 X 轴高位
#define MPU6050_GYRO_XOUT_L             0x44            // 陀螺仪 X 轴低位
#define MPU6050_GYRO_YOUT_H             0x45            // 陀螺仪 Y 轴高位
#define MPU6050_GYRO_YOUT_L             0x46            // 陀螺仪 Y 轴低位
#define MPU6050_GYRO_ZOUT_H             0x47            // 陀螺仪 Z 轴高位
#define MPU6050_GYRO_ZOUT_L             0x48            // 陀螺仪 Z 轴低位

/* 外部传感器数据写入寄存器 */
#define MPU6050_I2C_SLV0_DO             0x63
#define MPU6050_I2C_SLV1_DO             0x64
#define MPU6050_I2C_SLV2_DO             0x65
#define MPU6050_I2C_SLV3_DO             0x66

/* 系统控制寄存器 */
#define MPU6050_I2C_MST_DELAY_CTRL      0x67            // IIC 主机延时管理
#define MPU6050_SIGNAL_PATH_RESET       0x68            // 信号通道复位
#define MPU6050_MOT_DETECT_CTRL         0x69            // 运动检测控制
#define MPU6050_USER_CTRL               0x6A            // 用户控制寄存器
#define MPU6050_PWR_MGMT_1              0x6B            // 电源管理 1 (复位、时钟源)
#define MPU6050_PWR_MGMT_2              0x6C            // 电源管理 2 (休眠控制)

/* FIFO 计数与读写 */
#define MPU6050_FIFO_COUNT_H            0x72
#define MPU6050_FIFO_COUNT_L            0x73
#define MPU6050_FIFO_R_W                0x74

/* 器件身份 */
#define MPU6050_WHO_AM_I                0x75            // 器件 ID 寄存器 (默认 0x68)

extern I2C_HandleTypeDef hi2c1;

/* ================================================================================= */
/* [功能接口声明] 仅暴露对外公开的 API，提供核心功能调用接口                         */
/* ================================================================================= */

/* --- 顶层系统控制 --- */
void mpu6050_init(void);                                                                        // 初始化硬件并检查连接状态
uint8_t mpu6050_core_init(void);                                                                // 内核层基础初始化 (时钟树、采样率、量程)
void mpu6050_int_config_init(void);                                                             // 中断引脚触发逻辑配置

/* --- 底层突发读写接口 --- */
uint8_t mpu6050_burst_write(uint8_t reg_start_addr, uint8_t buffer_size, uint8_t *p_source_buf);// 突发写入数据缓冲区
uint8_t mpu6050_burst_read(uint8_t reg_start_addr, uint8_t buffer_size, uint8_t *p_dest_buf);   // 突发读取数据到缓冲区

/* --- 硬件参数配置 --- */
uint8_t mpu6050_set_gyro_scale(uint8_t scale_range);                                            // 设置陀螺仪满量程范围
uint8_t mpu6050_set_accel_scale(uint8_t scale_range);                                           // 设置加速度计满量程范围
uint8_t mpu6050_set_low_pass_filter(uint16_t cutoff_freq);                                      // 设置数字低通滤波器
uint8_t mpu6050_set_sample_rate(uint16_t sample_rate);                                          // 设置基础采样率

/* --- 原始数据获取 --- */
float mpu6050_get_temperature(void);                                                            // 获取转换后的环境温度值
uint8_t mpu6050_get_gyroscope(short *p_gyro_x, short *p_gyro_y, short *p_gyro_z);               // 获取未经处理的陀螺仪原始读数
uint8_t mpu6050_get_accelerometer(short *p_accel_x, short *p_accel_y, short *p_accel_z);        // 获取未经处理的加速度计原始读数
void mpu6050_read_all_data(int16_t *p_accel_x, int16_t *p_accel_y, int16_t *p_accel_z, int16_t *p_temp, int16_t *p_gyro_x, int16_t *p_gyro_y, int16_t *p_gyro_z); // 突发读取 14 字节全量数据

/* --- DMP 算法与高级功能 --- */
uint8_t mpu6050_dmp_init(void);                                                                 // DMP 引擎核心初始化
uint8_t mpu6050_dmp_get_data(float *p_pitch, float *p_roll, float *p_yaw);                      // 获取解算后的欧拉角数据
uint8_t mpu6050_run_self_test(void);                                                            // 执行硬件自检并校准传感器偏置

/* --- 辅助功能与测试 --- */
unsigned short inv_row_to_scale(const signed char *row);                                        // 辅助：处理坐标矩阵的行缩放逻辑
unsigned short inv_orientation_matrix_to_scalar(const signed char *mtx);                        // 辅助：坐标系矩阵转 DMP 标量
void mpu_get_ms_tick(unsigned long *time);                                                      // 库依赖占位函数
uint8_t mpu6050_burst_write_wrapper(uint8_t reg, uint8_t len, uint8_t *data);                   // DMP 库写接口适配层
uint8_t mpu6050_burst_read_wrapper(uint8_t reg, uint8_t len, uint8_t *data);                    // DMP 库读接口适配层
void mpu6050_test_print_loop(void);                                                             // 传感器全数据采集与串口打印测试

#endif /* __MPU6050_H__ */
