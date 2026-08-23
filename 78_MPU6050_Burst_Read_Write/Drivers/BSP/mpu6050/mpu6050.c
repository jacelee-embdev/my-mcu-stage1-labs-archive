/**
 * @file    mpu6050.c
 * @brief   MPU6050 软件模拟 I2C 驱动与业务逻辑实现
 */

#include "mpu6050.h"
#include "debug_usart.h"
#include <stdio.h>

/* ================================================================================= */
/* [私有底层驱动]                                                                    */
/* ================================================================================= */

/**
 * @brief  模拟 I2C 总线微秒级时延
 */
static void mpu6050_iic_delay(void)
{
    for (volatile uint32_t i = 0; i < 20; i++); 
}

/**
 * @brief  配置模拟 I2C 的 GPIO 引脚工作模式
 * @note   采用开漏输出以支持标准 I2C 的双向通讯特性并防止总线冲突
 */
static void mpu6050_gpio_init(void)
{
    GPIO_InitTypeDef gpio_init = {0};
    
    MPU6050_IIC_SCL_CLK_EN();
    MPU6050_IIC_SDA_CLK_EN();
    
    gpio_init.Mode  = GPIO_MODE_OUTPUT_OD;      // 开漏输出模式
    gpio_init.Pull  = GPIO_PULLUP;              // 上拉电阻
    gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
    
    gpio_init.Pin   = MPU6050_IIC_SCL_PIN;
    HAL_GPIO_Init(MPU6050_IIC_SCL_PORT, &gpio_init);
    
    gpio_init.Pin   = MPU6050_IIC_SDA_PIN;
    HAL_GPIO_Init(MPU6050_IIC_SDA_PORT, &gpio_init);
    
    MPU6050_SCL_H();
    MPU6050_SDA_H();
}

/**
 * @brief  产生 I2C 起始信号 (Start)
 */
static void mpu6050_iic_start(void)
{
    MPU6050_SDA_H();
    MPU6050_SCL_H();
    mpu6050_iic_delay();
    MPU6050_SDA_L();
    mpu6050_iic_delay();
    MPU6050_SCL_L();
}

/**
 * @brief  产生 I2C 终止信号 (Stop)
 */
static void mpu6050_iic_stop(void)
{
    MPU6050_SDA_L();
    MPU6050_SCL_H();
    mpu6050_iic_delay();
    MPU6050_SDA_H();
    mpu6050_iic_delay();
}

/**
 * @brief  主机发送应答信号
 */
static void mpu6050_iic_send_ack(uint8_t ack)
{
    if (ack) MPU6050_SDA_H();
    else     MPU6050_SDA_L();
    
    MPU6050_SCL_H();
    mpu6050_iic_delay();
    MPU6050_SCL_L();
    mpu6050_iic_delay();
}

/**
 * @brief  等待从机应答信号 (ACK Check)
 */
static uint8_t mpu6050_iic_receive_ack(void)
{
    uint32_t timeout = 0;
    
    MPU6050_SDA_H();                            // 释放总线进入输入监听
    mpu6050_iic_delay();
    MPU6050_SCL_H();                            // 时钟高电平期间采样
    mpu6050_iic_delay();
    
    while (MPU6050_SDA_READ())
    {
        timeout++;
        if (timeout > MPU6050_IIC_TIMEOUT)      // 超时防护
        {
            mpu6050_iic_stop();
            return 1;
        }
    }
    
    MPU6050_SCL_L();
    return 0;
}

/**
 * @brief  通过总线发送单字节数据
 */
static void mpu6050_iic_send_byte(uint8_t data)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        /* 阶段 1: 准备数据位 (MSB First) */
        if (data & 0x80) MPU6050_SDA_H();
        else             MPU6050_SDA_L();
        
        /* 阶段 2: 产生时钟脉冲通知从机读取 */
        mpu6050_iic_delay();
        MPU6050_SCL_H();
        mpu6050_iic_delay();
        MPU6050_SCL_L();
        data <<= 1;
    }
}

/**
 * @brief  通过总线接收单字节数据
 */
static uint8_t mpu6050_iic_receive_byte(void)
{
    uint8_t data = 0;
    MPU6050_SDA_H();                            // 释放 SDA 数据线
    
    for (uint8_t i = 0; i < 8; i++)
    {
        MPU6050_SCL_H();                        // 拉高时钟，此时总线数据保持稳定
        mpu6050_iic_delay();
        data <<= 1;
        if (MPU6050_SDA_READ()) data |= 0x01;   // 采样当前位
        MPU6050_SCL_L();                        // 拉低时钟，允许从机更新下一位
        mpu6050_iic_delay();
    }
    return data;
}

/**
 * @brief  向目标寄存器写入单字节数据
 */
static void mpu6050_write_register(uint8_t reg_addr, uint8_t data)
{
    mpu6050_iic_start();
    mpu6050_iic_send_byte((MPU6050_DEVICE_ADDR << 1) | 0x00);
    if (mpu6050_iic_receive_ack()) return;
    
    mpu6050_iic_send_byte(reg_addr);
    mpu6050_iic_receive_ack();
    
    mpu6050_iic_send_byte(data);
    mpu6050_iic_receive_ack();
    
    mpu6050_iic_stop();
}

/**
 * @brief  从目标寄存器读取单字节数据
 */
static uint8_t mpu6050_read_register(uint8_t reg_addr)
{
    uint8_t data = 0;
    
    /* 阶段 1: 指向目标寄存器地址 (Dummy Write) */
    mpu6050_iic_start();
    mpu6050_iic_send_byte((MPU6050_DEVICE_ADDR << 1) | 0x00);
    if (mpu6050_iic_receive_ack()) return 0xFF;
    
    mpu6050_iic_send_byte(reg_addr);
    mpu6050_iic_receive_ack();
    
    /* 阶段 2: 重新起始并切换为接收模式 */
    mpu6050_iic_start();
    mpu6050_iic_send_byte((MPU6050_DEVICE_ADDR << 1) | 0x01);
    mpu6050_iic_receive_ack();
    
    data = mpu6050_iic_receive_byte();
    mpu6050_iic_send_ack(1);                    // 接收完成，发送 NACK
    mpu6050_iic_stop();
    
    return data;
}

/* ================================================================================= */
/* [核心业务接口]                                                                    */
/* ================================================================================= */

/**
 * @brief  初始化 MPU6050 传感器
 */
uint8_t mpu6050_init(void)
{
    mpu6050_gpio_init();
    
    /* 配置初始化序列 */
    mpu6050_write_register(MPU6050_PWR_MGMT_1,   0x01); // 唤醒器件，选择 X 轴陀螺仪作为时钟源
    mpu6050_write_register(MPU6050_PWR_MGMT_2,   0x00); // 确保所有轴均处于激活状态
    mpu6050_write_register(MPU6050_SMPLRT_DIV,   0x09); // 设置采样频率为 100Hz
    mpu6050_write_register(MPU6050_CONFIG,       0x06); // 配置数字低通滤波器 (DLPF) 带宽 5Hz
    mpu6050_write_register(MPU6050_GYRO_CONFIG,  0x18); // 陀螺仪量程 +/-2000dps
    mpu6050_write_register(MPU6050_ACCEL_CONFIG, 0x18); // 加速度计量程 +/-16g
    
    /* 通讯自检 */
    uint8_t device_id = mpu6050_read_register(MPU6050_WHO_AM_I);
    if (device_id != 0x68)
    {
        printf("Error: MPU6050 ID Mismatch [0x%02X]\r\n", device_id);
        return 1;
    }
    
    return 0;
}

/**
 * @brief  向 MPU6050 连续写入数据缓冲区 (突发写)
 */
void mpu6050_burst_write(uint8_t reg_start_addr, uint8_t buffer_size, uint8_t *p_source_buf)
{
    /* 阶段 1: 建立寻址连接 */
    mpu6050_iic_start();
    mpu6050_iic_send_byte((MPU6050_DEVICE_ADDR << 1) | 0x00);
    if (mpu6050_iic_receive_ack()) return;
    
    mpu6050_iic_send_byte(reg_start_addr);
    mpu6050_iic_receive_ack();
    
    /* 阶段 2: 突发写入数据流 */
    for(uint8_t i = 0; i < buffer_size; i++)
    {
        mpu6050_iic_send_byte(p_source_buf[i]);
        if (mpu6050_iic_receive_ack()) break;          // 每字节检测应答，异常时中断
    }
    
    mpu6050_iic_stop();
}

/**
 * @brief  从 MPU6050 连续读取数据到缓冲区 (突发读)
 */
void mpu6050_burst_read(uint8_t reg_start_addr, uint8_t buffer_size, uint8_t *p_dest_buf)
{
    /* 阶段 1: 定位寄存器起始指针 */
    mpu6050_iic_start();
    mpu6050_iic_send_byte((MPU6050_DEVICE_ADDR << 1) | 0x00);
    if (mpu6050_iic_receive_ack()) return;
    
    mpu6050_iic_send_byte(reg_start_addr);
    mpu6050_iic_receive_ack();
    
    /* 阶段 2: 重新寻址切换读取方向 */
    mpu6050_iic_start();
    mpu6050_iic_send_byte((MPU6050_DEVICE_ADDR << 1) | 0x01);
    mpu6050_iic_receive_ack();
    
    /* 阶段 3: 批量拉取数据并处理应答流 */
    while(buffer_size--)
    {
        *(p_dest_buf++) = mpu6050_iic_receive_byte();
        
        /* 根据 I2C 协议：接收最后一个字节前发送 NACK 以终止通讯 */
        if(buffer_size == 0)    mpu6050_iic_send_ack(1);
        else                    mpu6050_iic_send_ack(0);
    }
    mpu6050_iic_stop();
}

/**
 * @brief  执行 MPU6050 通讯链路与寄存器读写诊断测试
 */
void mpu6050_test(void)
{
    printf("--- MPU6050 Diagnostic Start ---\r\n");
    
    /* 1. 器件 ID 检查 */
    uint8_t id = mpu6050_read_register(MPU6050_WHO_AM_I);
    printf("[CHECK] WHO_AM_I: 0x%02X\r\n", id);
    
    /* 2. 连续读写功能验证 */
    uint8_t test_tx[4] = {0x11, 0x2F, 0x3C, 0x4D};
    uint8_t test_rx[4] = {0};
    
    mpu6050_burst_write(MPU6050_SMPLRT_DIV, 4, test_tx);
    mpu6050_burst_read(MPU6050_SMPLRT_DIV, 4, test_rx);
    
    printf("[CHECK] Burst Read Result: %02X %02X %02X %02X\r\n", 
           test_rx[0], test_rx[1], test_rx[2], test_rx[3]);
    
    if (test_rx[0] == test_tx[0]) printf("Result: Communication Verified\r\n");
    else                          printf("Result: Communication Failure\r\n");
    
    printf("--- MPU6050 Diagnostic End ---\r\n");
}
