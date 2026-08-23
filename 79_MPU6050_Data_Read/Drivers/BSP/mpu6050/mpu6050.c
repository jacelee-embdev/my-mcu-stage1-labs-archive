/**
 * @file    mpu6050.c
 * @brief   MPU6050 软件模拟 I2C 驱动与业务逻辑实现
 */

#include "mpu6050.h"
#include "debug_usart.h"
#include "stdio.h"

/* ================================================================================= */
/* [私有底层驱动]                                                                    */
/* ================================================================================= */

// 模拟 I2C 总线微秒级时延，用于满足时序建立时间
static void mpu6050_iic_delay(void)
{
    /* 依据主频设定的空循环，确保时钟频率不超过 400kHz 快速模式上限 */
    for (volatile uint32_t i = 0; i < 20; i++); 
}

// 配置模拟 I2C 的 GPIO 引脚工作模式
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
        MPU6050_SDA_H();  // 释放总线发送 NACK (非应答)
    }
    else     
    {
        MPU6050_SDA_L();  // 拉低总线发送 ACK (应答)
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

// 向目标寄存器写入单字节数据
static void mpu6050_write_register(uint8_t reg_addr, uint8_t write_data)
{
    mpu6050_iic_start();
    
    /* 阶段 1: 发送设备寻址字 (写方向) */
    mpu6050_iic_send_byte((MPU6050_DEVICE_ADDR << 1) | 0x00);
    if (mpu6050_iic_wait_ack()) return;
    
    /* 阶段 2: 发送寄存器内部地址 */
    mpu6050_iic_send_byte(reg_addr);
    mpu6050_iic_wait_ack();
    
    /* 阶段 3: 写入有效负载数据 */
    mpu6050_iic_send_byte(write_data);
    mpu6050_iic_wait_ack();
    
    mpu6050_iic_stop();
}

// 从目标寄存器读取单字节数据
static uint8_t mpu6050_read_register(uint8_t reg_addr)
{
    uint8_t read_data = 0;
    
    /* 阶段 1: 虚拟写操作 (Dummy Write) 设定内部寄存器指针 */
    mpu6050_iic_start();
    mpu6050_iic_send_byte((MPU6050_DEVICE_ADDR << 1) | 0x00);
    if (mpu6050_iic_wait_ack()) return 0xFF;
    
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

/* ================================================================================= */
/* [核心业务接口]                                                                    */
/* ================================================================================= */

void mpu6050_burst_write(uint8_t reg_start_addr, uint8_t buffer_size, uint8_t *p_source_buf)
{
    /* 阶段 1: 建立寻址连接与寄存器定位 */
    mpu6050_iic_start();
    mpu6050_iic_send_byte((MPU6050_DEVICE_ADDR << 1) | 0x00);
    if (mpu6050_iic_wait_ack()) return;
    
    mpu6050_iic_send_byte(reg_start_addr);
    mpu6050_iic_wait_ack();
    
    /* 阶段 2: 突发写入数据流 */
    for (uint8_t i = 0; i < buffer_size; i++)
    {
        mpu6050_iic_send_byte(p_source_buf[i]);
        if (mpu6050_iic_wait_ack()) break;      // 逐字节检测应答，发生异常主动退出透传
    }
    
    mpu6050_iic_stop();
}

void mpu6050_burst_read(uint8_t reg_start_addr, uint8_t buffer_size, uint8_t *p_dest_buf)
{
    /* 阶段 1: 定位寄存器起始读指针 */
    mpu6050_iic_start();
    mpu6050_iic_send_byte((MPU6050_DEVICE_ADDR << 1) | 0x00);
    if (mpu6050_iic_wait_ack()) return;
    
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
}

void mpu6050_read_all_data(int16_t *p_accel_x, int16_t *p_accel_y, int16_t *p_accel_z, int16_t *p_temp, int16_t *p_gyro_x, int16_t *p_gyro_y, int16_t *p_gyro_z)
{
    uint8_t buffer[14] = {0};
    
    /* 阶段 1: 从加速度计 X 轴高位起始地址开始，连续拉取 14 字节完整数据流 */
    /* 数据分布: 6字节加速度 + 2字节温度 + 6字节陀螺仪 */
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

uint8_t mpu6050_init(void)
{
    mpu6050_gpio_init();
    
    /* 阶段 1: 唤醒并配置时钟树 */
    mpu6050_write_register(MPU6050_PWR_MGMT_1,   0x01); // 唤醒器件，选用 X 轴陀螺仪 PLL 作为稳定主时钟源
    mpu6050_write_register(MPU6050_PWR_MGMT_2,   0x00); // 确保所有六轴传感节点均处于激活运行状态
    
    /* 阶段 2: 配置采样率与数字滤波器 (DLPF) */
    mpu6050_write_register(MPU6050_SMPLRT_DIV,   0x09); // 1kHz / (1 + 9) = 100Hz 基础采样频率
    mpu6050_write_register(MPU6050_CONFIG,       0x06); // DLPF 配置 5Hz 截止频率，平滑高频震动噪声
    
    /* 阶段 3: 配置满量程物理测量范围 */
    mpu6050_write_register(MPU6050_GYRO_CONFIG,  0x18); // 陀螺仪量程设定为 +/- 2000 dps (0x18 -> 满量程)
    mpu6050_write_register(MPU6050_ACCEL_CONFIG, 0x18); // 加速度计量程设定为 +/- 16g (0x18 -> 满量程)
    
    /* 阶段 4: I2C 通讯物理链路自检 */
    uint8_t device_id = mpu6050_read_register(MPU6050_WHO_AM_I);
    if (device_id != 0x68)
    {
        printf("Error: MPU6050 ID Mismatch [0x%02X]\r\n", device_id);
        return 1;                                       // 器件 ID 不匹配，返回异常错误码
    }
    
    return 0;                                           // 初始化挂载成功
}

/**
 * @brief  MPU6050 全数据采集与串口打印测试函数
 * @note   该函数适配了突发读取接口，并严格保留了原有的延时函数命名习惯
 */
void mpu6050_test_print_loop(void)
{
    /* 定义原始数据变量，采用语义化命名 */
    int16_t accel_x, accel_y, accel_z;
    int16_t gyro_x,  gyro_y,  gyro_z;
    int16_t temp_raw;

    printf("MPU6050 Data Streaming Started...\r\n");

        /* 1. 调用重构后的突发读取接口，获取包含温度在内的完整 14 字节数据 */
        mpu6050_read_all_data(&accel_x, &accel_y, &accel_z, 
                              &temp_raw, 
                              &gyro_x,  &gyro_y,  &gyro_z);

        /* 2. 格式化输出 */
        printf("AX:%d, AY:%d, AZ:%d, TEMP:%d, GX:%d, GY:%d, GZ:%d\r\n",
               accel_x, accel_y, accel_z,
               temp_raw,
               gyro_x,  gyro_y,  gyro_z);

}
