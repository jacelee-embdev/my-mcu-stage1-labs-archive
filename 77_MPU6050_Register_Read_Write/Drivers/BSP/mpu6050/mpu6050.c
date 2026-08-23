#include "mpu6050.h"
#include "debug_usart.h"

/**
 * @brief 初始化 MPU6050 的 GPIO 引脚 (模拟 I2C)
 */
void mpu6050_gpio_init(void)
{
    GPIO_InitTypeDef gpio_initstruct;
    
    MPU6050_IIC_SCL_CLK_EN();
    MPU6050_IIC_SDA_CLK_EN();
    
    gpio_initstruct.Mode  = GPIO_MODE_OUTPUT_OD; 
    gpio_initstruct.Pull  = GPIO_PULLUP;
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;
    
    // 初始化 SCL
    gpio_initstruct.Pin   = MPU6050_IIC_SCL_PIN;
    HAL_GPIO_Init(MPU6050_IIC_SCL_PORT, &gpio_initstruct);
    
    // 初始化 SDA
    gpio_initstruct.Pin   = MPU6050_IIC_SDA_PIN;
    HAL_GPIO_Init(MPU6050_IIC_SDA_PORT, &gpio_initstruct);
    
    MPU6050_SCL_H();
    MPU6050_SDA_H();
}

/**
 * @brief I2C 起始信号: SCL 高电平时，SDA 由高变低
 */
void mpu6050_iic_start(void)
{
    MPU6050_SDA_H();
    MPU6050_SCL_H();
    MPU6050_SDA_L();
    MPU6050_SCL_L();
}

/**
 * @brief I2C 停止信号: SCL 高电平时，SDA 由低变高
 */
void mpu6050_iic_stop(void)
{
    MPU6050_SDA_L();
    MPU6050_SCL_H();
    MPU6050_SDA_H();
}

/**
 * @brief I2C 发送应答/非应答信号
 * @param ack 0:应答, 1:非应答
 */
void mpu6050_iic_send_ack(uint8_t ack)
{
    if (ack) MPU6050_SDA_H();
    else     MPU6050_SDA_L();
    
    MPU6050_SCL_H();
    MPU6050_SCL_L();
}

/**
 * @brief I2C 等待从机应答信号
 * @return uint8_t 0: 接收到应答, 1: 未收到应答
 */
uint8_t mpu6050_iic_receive_ack(void)
{
    uint8_t ack;
    MPU6050_SDA_H(); // 释放总线
    MPU6050_SCL_H();
    ack = MPU6050_SDA_READ();
    MPU6050_SCL_L();
    return ack;
}

/**
 * @brief I2C 发送一个字节 (MSB先行)
 */
void mpu6050_iic_send_byte(uint8_t data)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        if (data & 0x80) MPU6050_SDA_H();
        else             MPU6050_SDA_L();
        
        MPU6050_SCL_H();
        MPU6050_SCL_L();
        data <<= 1;
    }
}

/**
 * @brief I2C 读取一个字节
 */
uint8_t mpu6050_iic_receive_byte(void)
{
    uint8_t data = 0;
    MPU6050_SDA_H(); // 释放总线
    
    for (uint8_t i = 0; i < 8; i++)
    {
        MPU6050_SCL_H();
        data <<= 1;
        if (MPU6050_SDA_READ()) data |= 0x01;
        MPU6050_SCL_L();
    }
    return data;
}

void mpu6050_iic_write_register(uint8_t address,uint8_t data)
{
    //IIC起始信号
    mpu6050_iic_start();
    //发送从机地址
    mpu6050_iic_send_byte((MPU6050_ADDRESS << 1) | 0x00);
    //等待从机响应
    mpu6050_iic_receive_ack();
    //发送寄存器地址
    mpu6050_iic_send_byte(address);
    //等待从机响应
    mpu6050_iic_receive_ack();
    //发送写入的数据
    mpu6050_iic_send_byte(data);
    //等待从机响应
    mpu6050_iic_receive_ack();
    //IIC终止信号
    mpu6050_iic_stop();
}

uint8_t mpu6050_iic_read_register(uint8_t address)
{
    uint8_t data = 0;
    //IIC起始信号
    mpu6050_iic_start();
    //发送从机地址
    mpu6050_iic_send_byte((MPU6050_ADDRESS << 1) | 0x00);
    //等待从机响应
    mpu6050_iic_receive_ack();
    //发送寄存器地址
    mpu6050_iic_send_byte(address);
    //等待从机响应
    mpu6050_iic_receive_ack();
    
    //IIC再次起始信号
    mpu6050_iic_start();
    //发送从机地址
    mpu6050_iic_send_byte((MPU6050_ADDRESS << 1) | 0x01);
    //等待从机响应
     mpu6050_iic_receive_ack();
    
    //接收从机数据
    data = mpu6050_iic_receive_byte();
    //给从机应答(ack 1)
    mpu6050_iic_send_ack(1);
    //IIC终止信号
    mpu6050_iic_stop();
    
    return data;
}

/**
 * @brief MPU6050 初始化
 */
void mpu6050_init(void)
{
    mpu6050_gpio_init();
}

/**
 * @brief MPU6050 通讯测试
 */
void mpu6050_test(void)
{
    /* TEST1 */
    mpu6050_iic_start();
    
    // 发送设备地址 + 写位
    mpu6050_iic_send_byte((MPU6050_ADDRESS << 1) | 0x00);
    uint8_t ack = mpu6050_iic_receive_ack();
    
    printf("MPU6050 ACK Status: %d\r\n", ack);
    
    mpu6050_iic_stop();
    
    
    /* TEST2 */
    uint8_t id = mpu6050_iic_read_register(0x75);
    printf("id:%x\r\n",id);
    
    /* TEST3 */
    mpu6050_iic_write_register(0x6B,0x00);  //唤醒睡眠
    mpu6050_iic_write_register(0x19,0xAA);
    uint8_t data = mpu6050_iic_read_register(0x19);
    printf("data:%X\r\n",data);
}
