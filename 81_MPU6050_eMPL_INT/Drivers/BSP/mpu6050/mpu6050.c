/**
 * @file    mpu6050.c
 * @brief   MPU6050 软件模拟 I2C 驱动与业务逻辑实现
 */

#include "mpu6050.h"
#include "delay.h"
#include "debug_usart.h"
#include "stdio.h"

/* ================================================================================= */
/* [私有全局变量区] 隔离内部数据栈，防止全局命名污染                                 */
/* ================================================================================= */

static signed char gyro_orientation[9] = { 1, 0, 0,
                                           0, 1, 0,
                                           0, 0, 1};

/* ================================================================================= */
/* [私有底层驱动] 物理总线层：负责最基础的时序控制与电平翻转                         */
/* ================================================================================= */

// 模拟 I2C 总线微秒级时延，用于满足时序建立时间
static void mpu6050_iic_delay(void)
{
    /* 依据主频设定的空循环，确保时钟频率不超过 400kHz 快速模式上限 */
    for (volatile uint32_t i = 0; i < 20; i++); 
}

// 物理层初始化：配置模拟 I2C 的 GPIO 引脚工作模式
static void mpu6050_gpio_init(void)
{
    GPIO_InitTypeDef gpio_init = {0};
    
    MPU6050_IIC_SCL_CLK_EN();
    MPU6050_IIC_SDA_CLK_EN();
    
    /* 采用开漏输出以支持标准 I2C 的双向通讯特性（线与逻辑）并防止总线短路冲突 */
    gpio_init.Mode  = GPIO_MODE_OUTPUT_OD;      
    gpio_init.Pull  = GPIO_PULLUP;              
    gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
    
    gpio_init.Pin   = MPU6050_IIC_SCL_PIN;
    HAL_GPIO_Init(MPU6050_IIC_SCL_PORT, &gpio_init);
    
    gpio_init.Pin   = MPU6050_IIC_SDA_PIN;
    HAL_GPIO_Init(MPU6050_IIC_SDA_PORT, &gpio_init);
    
    /* 默认释放总线，使 SCL 和 SDA 保持高电平空闲状态 */
    MPU6050_SCL_H();
    MPU6050_SDA_H();
}

// 产生 I2C 起始信号 (Start)
static void mpu6050_iic_start(void)
{
    MPU6050_SDA_H();
    MPU6050_SCL_H();
    mpu6050_iic_delay();
    
    /* 阶段 1: SCL 高电平期间，SDA 产生下降沿触发起始信号 */
    MPU6050_SDA_L();
    mpu6050_iic_delay();
    
    /* 阶段 2: 钳住总线准备发送或接收 */
    MPU6050_SCL_L();
}

// 产生 I2C 终止信号 (Stop)
static void mpu6050_iic_stop(void)
{
    MPU6050_SDA_L();
    MPU6050_SCL_H();
    mpu6050_iic_delay();
    
    /* 阶段 1: SCL 高电平期间，SDA 产生上升沿触发终止信号 */
    MPU6050_SDA_H();
    mpu6050_iic_delay();
}

// 主机发送应答信号
static void mpu6050_iic_send_ack(uint8_t ack_status)
{
    if (ack_status) 
    {
        MPU6050_SDA_H();                        // 释放总线发送 NACK (非应答)
    }
    else     
    {
        MPU6050_SDA_L();                        // 拉低总线发送 ACK (应答)
    }
    
    MPU6050_SCL_H();
    mpu6050_iic_delay();
    MPU6050_SCL_L();
    mpu6050_iic_delay();
}

// 等待从机应答信号 (ACK Check)
static uint8_t mpu6050_iic_wait_ack(void)
{
    uint32_t timeout = 0;
    
    MPU6050_SDA_H();                            // 释放总线进入输入监听状态
    mpu6050_iic_delay();
    MPU6050_SCL_H();                            // 拉高时钟线进行电平采样
    mpu6050_iic_delay();
    
    /* 阶段 1: 轮询 SDA 状态，低电平为有效应答 */
    while (MPU6050_SDA_READ())
    {
        timeout++;
        if (timeout > MPU6050_IIC_TIMEOUT)      // 触发超时防护，主动释放总线避免死锁
        {
            mpu6050_iic_stop();
            return 1;                           // 返回 1 表示无应答
        }
    }
    
    MPU6050_SCL_L();                            // 拉低时钟，继续后续数据流
    return 0;                                   // 返回 0 表示应答成功
}

// 通过总线发送单字节数据
static void mpu6050_iic_send_byte(uint8_t tx_data)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        /* 阶段 1: 准备数据位 (MSB 先行) */
        if (tx_data & 0x80) 
        {
            MPU6050_SDA_H();
        }
        else             
        {
            MPU6050_SDA_L();
        }
        
        /* 阶段 2: 产生时钟脉冲通知从机读取数据 */
        mpu6050_iic_delay();
        MPU6050_SCL_H();
        mpu6050_iic_delay();
        MPU6050_SCL_L();
        tx_data <<= 1;
    }
}

// 通过总线接收单字节数据
static uint8_t mpu6050_iic_receive_byte(void)
{
    uint8_t rx_data = 0;
    
    MPU6050_SDA_H();                            // 主机释放 SDA 数据线，交由从机控制电平
    
    for (uint8_t i = 0; i < 8; i++)
    {
        MPU6050_SCL_H();                        // 拉高时钟，此时总线数据保持稳定可读
        mpu6050_iic_delay();
        
        rx_data <<= 1;
        if (MPU6050_SDA_READ()) 
        {
            rx_data |= 0x01;                    // 采样当前数据位
        }
        
        MPU6050_SCL_L();                        // 拉低时钟，允许从机更新下一位电平
        mpu6050_iic_delay();
    }
    return rx_data;
}

/* ================================================================================= */
/* [寄存器接口层] 逻辑处理层：封装寻址与批量透传功能                                 */
/* ================================================================================= */

// 向目标寄存器写入单字节数据
static uint8_t mpu6050_write_register(uint8_t reg_addr, uint8_t write_data)
{
    mpu6050_iic_start();
    
    /* 阶段 1: 发送设备寻址字 (写方向) */
    mpu6050_iic_send_byte((MPU6050_DEVICE_ADDR << 1) | 0x00);
    if (mpu6050_iic_wait_ack()) 
    {
        mpu6050_iic_stop();
        return 1;
    }
    
    /* 阶段 2: 发送寄存器内部地址 */
    mpu6050_iic_send_byte(reg_addr);
    mpu6050_iic_wait_ack();
    
    /* 阶段 3: 写入有效负载数据 */
    mpu6050_iic_send_byte(write_data);
    mpu6050_iic_wait_ack();
    
    mpu6050_iic_stop();
    return 0;
}

// 从目标寄存器读取单字节数据
static uint8_t mpu6050_read_register(uint8_t reg_addr)
{
    uint8_t read_data = 0;
    
    /* 阶段 1: 虚拟写操作 (Dummy Write) 设定内部寄存器指针 */
    mpu6050_iic_start();
    mpu6050_iic_send_byte((MPU6050_DEVICE_ADDR << 1) | 0x00);
    if (mpu6050_iic_wait_ack()) 
    {
        mpu6050_iic_stop();
        return 0xFF;
    }
    
    mpu6050_iic_send_byte(reg_addr);
    mpu6050_iic_wait_ack();
    
    /* 阶段 2: 重新发起起始信号，切换为读取流向 */
    mpu6050_iic_start();
    mpu6050_iic_send_byte((MPU6050_DEVICE_ADDR << 1) | 0x01);
    mpu6050_iic_wait_ack();
    
    /* 阶段 3: 接收有效负载并回复停止时序 */
    read_data = mpu6050_iic_receive_byte();
    mpu6050_iic_send_ack(1);                    // 接收完成，主机返回 NACK 通知停止发送
    mpu6050_iic_stop();
    
    return read_data;
}

// 突发写入数据缓冲区到目标寄存器
uint8_t mpu6050_burst_write(uint8_t reg_start_addr, uint8_t buffer_size, uint8_t *p_source_buf)
{
    /* 阶段 1: 建立寻址连接与寄存器定位 */
    mpu6050_iic_start();
    mpu6050_iic_send_byte((MPU6050_DEVICE_ADDR << 1) | 0x00);
    if (mpu6050_iic_wait_ack()) 
    {
        mpu6050_iic_stop();
        return 1;
    }
    
    mpu6050_iic_send_byte(reg_start_addr);
    mpu6050_iic_wait_ack();
    
    /* 阶段 2: 突发写入数据流 */
    for (uint8_t i = 0; i < buffer_size; i++)
    {
        mpu6050_iic_send_byte(p_source_buf[i]);
        if (mpu6050_iic_wait_ack()) break;      // 逐字节检测应答，发生异常主动退出透传
    }
    
    mpu6050_iic_stop();
    return 0;
}

// 从目标寄存器突发读取数据到缓冲区
uint8_t mpu6050_burst_read(uint8_t reg_start_addr, uint8_t buffer_size, uint8_t *p_dest_buf)
{
    /* 阶段 1: 定位寄存器起始读指针 */
    mpu6050_iic_start();
    mpu6050_iic_send_byte((MPU6050_DEVICE_ADDR << 1) | 0x00);
    if (mpu6050_iic_wait_ack()) 
    {
        mpu6050_iic_stop();
        return 1;
    }
    
    mpu6050_iic_send_byte(reg_start_addr);
    mpu6050_iic_wait_ack();
    
    /* 阶段 2: 重新寻址切换至读取工作模式 */
    mpu6050_iic_start();
    mpu6050_iic_send_byte((MPU6050_DEVICE_ADDR << 1) | 0x01);
    mpu6050_iic_wait_ack();
    
    /* 阶段 3: 批量拉取数据并维护应答时序流 */
    while (buffer_size--)
    {
        *(p_dest_buf++) = mpu6050_iic_receive_byte();
        
        /* 协议规范: 接收倒数第一个字节后，必须返回 NACK 中止后续透传 */
        if (buffer_size == 0)    
        {
            mpu6050_iic_send_ack(1);
        }
        else                    
        {
            mpu6050_iic_send_ack(0);
        }
    }
    mpu6050_iic_stop();
    return 0;
}

// DMP 库写接口适配层 (I2C 写入包装函数)
uint8_t mpu6050_burst_write_wrapper(uint8_t reg, uint8_t len, uint8_t *data)
{
    mpu6050_burst_write(reg, len, data); 
    return 0; 
}

// DMP 库读接口适配层 (I2C 读取包装函数)
uint8_t mpu6050_burst_read_wrapper(uint8_t reg, uint8_t len, uint8_t *data)
{
    return mpu6050_burst_read(reg, len, data); 
}

/* ================================================================================= */
/* [硬件配置层] 外设特性配置与系统唤醒                                               */
/* ================================================================================= */

// 设置陀螺仪满量程范围
uint8_t mpu6050_set_gyro_scale(uint8_t scale_range)
{
    /* scale_range 映射: 0:±250dps | 1:±500dps | 2:±1000dps | 3:±2000dps */
    return mpu6050_write_register(MPU6050_GYRO_CONFIG, scale_range << 3);
}

// 设置加速度计满量程范围
uint8_t mpu6050_set_accel_scale(uint8_t scale_range)
{
    /* scale_range 映射: 0:±2g | 1:±4g | 2:±8g | 3:±16g */
    return mpu6050_write_register(MPU6050_ACCEL_CONFIG, scale_range << 3);
}

// 设置数字低通滤波器 (DLPF)
uint8_t mpu6050_set_low_pass_filter(uint16_t cutoff_freq)
{
    uint8_t data = 0;
    
    if (cutoff_freq >= 188)      data = 1;
    else if (cutoff_freq >= 98)  data = 2;
    else if (cutoff_freq >= 42)  data = 3;
    else if (cutoff_freq >= 20)  data = 4;
    else if (cutoff_freq >= 10)  data = 5;
    else                         data = 6;
    
    return mpu6050_write_register(MPU6050_CONFIG, data);
}

// 设置基础采样率
uint8_t mpu6050_set_sample_rate(uint16_t sample_rate)
{
    uint8_t data;
    
    if (sample_rate > 1000)     sample_rate = 1000;
    else if (sample_rate < 4)   sample_rate = 4;
    
    /* 采样率分频公式: Sample_Rate = Internal_Sample_Rate / (1 + SMPLRT_DIV) */
    data = 1000 / sample_rate - 1;
    mpu6050_write_register(MPU6050_SMPLRT_DIV, data);
    
    return mpu6050_set_low_pass_filter(sample_rate / 2);
}

// 内核层基础初始化 (时钟树、采样率、量程等核心寄存器挂载)
uint8_t mpu6050_core_init(void)
{
    uint8_t device_id = mpu6050_read_register(MPU6050_WHO_AM_I);
    
    if (device_id == MPU6050_DEVICE_ADDR)
    {
        /* 阶段 1: 唤醒并配置时钟树 */
        mpu6050_write_register(MPU6050_PWR_MGMT_1,   0x01); // 唤醒器件，选用 X 轴陀螺仪 PLL 作为稳定主时钟源
        mpu6050_write_register(MPU6050_PWR_MGMT_2,   0x00); // 确保所有六轴传感节点均处于激活运行状态
        
        /* 阶段 2: 配置采样率与数字滤波器 (DLPF) */
        mpu6050_write_register(MPU6050_SMPLRT_DIV,   0x09); // 1kHz / (1 + 9) = 100Hz 基础采样频率
        mpu6050_write_register(MPU6050_CONFIG,       0x06); // DLPF 配置 5Hz 截止频率，平滑高频震动噪声
        
        /* 阶段 3: 配置满量程物理测量范围 */
        mpu6050_write_register(MPU6050_GYRO_CONFIG,  0x18); // 陀螺仪量程设定为 +/- 2000 dps (0x18 -> 满量程)
        mpu6050_write_register(MPU6050_ACCEL_CONFIG, 0x18); // 加速度计量程设定为 +/- 16g (0x18 -> 满量程)
        
        return 0;                                           // 初始化挂载成功
    }
    else
    {
        printf("Error: MPU6050 ID Mismatch [0x%02X]\r\n", device_id);
        return 1;                                           // 器件 ID 不匹配，返回异常错误码
    }
}

// 中断引脚触发逻辑配置
void mpu6050_int_config_init(void)
{
    mpu6050_write_register(MPU6050_INT_ENABLE,  0x01);
    mpu6050_write_register(MPU6050_INT_PIN_CFG, 0x80);
}

/* ================================================================================= */
/* [数据采集层] 面向业务的传感器原始数据读取                                         */
/* ================================================================================= */

// 获取未经处理的陀螺仪原始读数
uint8_t mpu6050_get_gyroscope(short *p_gyro_x, short *p_gyro_y, short *p_gyro_z)
{
    uint8_t buffer[6], res;
    
    res = mpu6050_burst_read(MPU6050_GYRO_XOUT_H, 6, buffer);
    if (res == 0)
    {
        *p_gyro_x = ((uint16_t)buffer[0] << 8) | buffer[1];
        *p_gyro_y = ((uint16_t)buffer[2] << 8) | buffer[3];
        *p_gyro_z = ((uint16_t)buffer[4] << 8) | buffer[5];
    }
    return res;
}

// 获取未经处理的加速度计原始读数
uint8_t mpu6050_get_accelerometer(short *p_accel_x, short *p_accel_y, short *p_accel_z)
{
    uint8_t buffer[6], res;
    
    res = mpu6050_burst_read(MPU6050_ACCEL_XOUT_H, 6, buffer);
    if (res == 0)
    {
        *p_accel_x = ((uint16_t)buffer[0] << 8) | buffer[1];
        *p_accel_y = ((uint16_t)buffer[2] << 8) | buffer[3];
        *p_accel_z = ((uint16_t)buffer[4] << 8) | buffer[5];
    }
    return res;
}

// 获取转换后的环境温度值
float mpu6050_get_temperature(void)
{
    unsigned char buffer[2];
    short raw;
    float temp;
    
    mpu6050_burst_read(MPU6050_TEMP_OUT_H, 2, buffer);
    raw = (buffer[0] << 8) | buffer[1];
    
    /* 官方温度换算公式 */
    temp = (36.53f + ((double)raw) / 340.0f) * 100.0f;
    return temp / 100.0f;
}

// 突发读取 14 字节全量原始数据
void mpu6050_read_all_data(int16_t *p_accel_x, int16_t *p_accel_y, int16_t *p_accel_z, int16_t *p_temp, int16_t *p_gyro_x, int16_t *p_gyro_y, int16_t *p_gyro_z)
{
    uint8_t buffer[14] = {0};
    
    /* 阶段 1: 从加速度计 X 轴高位起始地址开始，连续拉取 14 字节完整数据流 */
    mpu6050_burst_read(MPU6050_ACCEL_XOUT_H, 14, buffer);
    
    /* 阶段 2: 拼接高低 8 位，还原 16 位有符号原始数据 */
    *p_accel_x = (buffer[0]  << 8) | buffer[1];
    *p_accel_y = (buffer[2]  << 8) | buffer[3];
    *p_accel_z = (buffer[4]  << 8) | buffer[5];
    *p_temp    = (buffer[6]  << 8) | buffer[7];
    *p_gyro_x  = (buffer[8]  << 8) | buffer[9];
    *p_gyro_y  = (buffer[10] << 8) | buffer[11];
    *p_gyro_z  = (buffer[12] << 8) | buffer[13];
}

/* ================================================================================= */
/* [高级算法层] 姿态解算引擎 (DMP) 移植与调用                                        */
/* ================================================================================= */

// 辅助：处理坐标矩阵的行缩放逻辑
unsigned short inv_row_to_scale(const signed char *row)
{
    unsigned short b;
    
    if (row[0] > 0)         b = 0;
    else if (row[0] < 0)    b = 4;
    else if (row[1] > 0)    b = 1;
    else if (row[1] < 0)    b = 5;
    else if (row[2] > 0)    b = 2;
    else if (row[2] < 0)    b = 6;
    else                    b = 7;
    
    return b;
}

// 辅助：坐标系矩阵转 DMP 标量
unsigned short inv_orientation_matrix_to_scalar(const signed char *mtx)
{
    unsigned short scalar;
    
    scalar  = inv_row_to_scale(mtx);
    scalar |= inv_row_to_scale(mtx + 3) << 3;
    scalar |= inv_row_to_scale(mtx + 6) << 6;
    
    return scalar;
}

// 执行硬件自检并校准传感器偏置
uint8_t mpu6050_run_self_test(void)
{
    int result;
    long gyro[3], accel[3];
    
    result = mpu_run_self_test(gyro, accel);
    
    if (result == 0x03)
    {
        float sens;
        unsigned short accel_sens;
        
        /* 1. 陀螺仪偏置补偿 (抑制 Yaw 轴漂移) */
        mpu_get_gyro_sens(&sens);
        gyro[0] = (long)(gyro[0] * sens);
        gyro[1] = (long)(gyro[1] * sens);
        gyro[2] = (long)(gyro[2] * sens);
        dmp_set_gyro_bias(gyro); 
        
        /* 2. 加速度计偏置补偿 (硬件级缩放修正) */
        mpu_get_accel_sens(&accel_sens);
        accel[0] *= accel_sens;
        accel[1] *= accel_sens;
        accel[2] *= accel_sens;
        
        // 注释掉 dmp_set_accel_bias，避免因官方底层缩放逻辑 Bug 导致 Roll/Pitch 出现 20~30 度的巨大静态误差 
//      dmp_set_accel_bias(accel);
        
        return 0;
    }
    else 
    {
        return 1;
    }
}

// DMP 引擎核心初始化
uint8_t mpu6050_dmp_init(void)
{
    uint8_t res = 0;
    
    if (mpu_init(NULL) == 0)
    {
        res = mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL);
        if (res) return 1;
        
        res = mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL);
        if (res) return 2;
        
        res = mpu_set_sample_rate(DEFAULT_MPU_HZ);
        if (res) return 3;
        
        res = dmp_load_motion_driver_firmware();
        if (res) return 4;
        
        res = dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation));
        if (res) return 5;
        
        res = dmp_enable_feature(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_TAP | DMP_FEATURE_ANDROID_ORIENT |
                                 DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO | DMP_FEATURE_GYRO_CAL);
        if (res) return 6;
        
        res = dmp_set_fifo_rate(DEFAULT_MPU_HZ);
        if (res) return 7;
        
        res = mpu6050_run_self_test();
        if (res) return 8;
        
        res = mpu_set_dmp_state(1);
        if (res) return 9;
    }
    else    
    {
        return 10;
    }
    
    mpu6050_int_config_init();
    return 0;
}

// 获取解算后的欧拉角数据
uint8_t mpu6050_dmp_get_data(float *p_pitch, float *p_roll, float *p_yaw)
{
    float q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f;
    unsigned long sensor_timestamp;
    short gyro[3], accel[3], sensors;
    unsigned char more;
    long quat[4];
    
    if (dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors, &more)) return 1;
    
    if (sensors & INV_WXYZ_QUAT)
    {
        q0 = quat[0] / Q30_FORMAT_DIVISOR;
        q1 = quat[1] / Q30_FORMAT_DIVISOR;
        q2 = quat[2] / Q30_FORMAT_DIVISOR;
        q3 = quat[3] / Q30_FORMAT_DIVISOR;
        
        *p_pitch = asin(-2 * q1 * q3 + 2 * q0 * q2) * 57.3f;
        *p_roll  = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2 * q2 + 1) * 57.3f;
        *p_yaw   = atan2(2 * (q1 * q2 + q0 * q3), q0 * q0 + q1 * q1 - q2 * q2 - q3 * q3) * 57.3f;
    }
    else 
    {
        return 2;
    }
    return 0;
}

/* ================================================================================= */
/* [应用接口层] 外部调度与业务聚合封装                                               */
/* ================================================================================= */

// 初始化硬件并检查连接状态
void mpu6050_init(void)
{
    uint8_t err_code;
    
    mpu6050_gpio_init();
    mpu6050_core_init();
    HAL_Delay(100);
    
    while ((err_code = mpu6050_dmp_init()) != 0)
    {
        printf("DMP Init Failed! Error code: %d\r\n", err_code);
        HAL_Delay(20);
    }
    printf("Mpu6050 Init Success!\r\n");
}

// 传感器全数据采集与串口打印测试
void mpu6050_test_print_loop(void)
{
    int16_t accel_x, accel_y, accel_z;
    int16_t gyro_x,  gyro_y,  gyro_z;
    int16_t temp_raw;

    printf("MPU6050 Data Streaming Started...\r\n");

    /* 调用突发读取接口获取 14 字节完整数据 */
    mpu6050_read_all_data(&accel_x, &accel_y, &accel_z, 
                          &temp_raw, 
                          &gyro_x,  &gyro_y,  &gyro_z);

    printf("AX:%d, AY:%d, AZ:%d, TEMP:%d, GX:%d, GY:%d, GZ:%d\r\n",
           accel_x, accel_y, accel_z,
           temp_raw,
           gyro_x,  gyro_y,  gyro_z);
}

// 库依赖时间滴答占位函数
void mpu_get_ms_tick(unsigned long *time)
{
    /* 暂无外部依赖调用需求，保留占位 */
}
