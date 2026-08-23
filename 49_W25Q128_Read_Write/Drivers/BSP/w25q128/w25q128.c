#include "w25q128.h"
#include "uart1.h"
#include "delay.h"

SPI_HandleTypeDef spi_handle = {0};

// SPI1 初始化配置
void w25q128_spi_init(void)
{
    spi_handle.Instance = SPI1;
    spi_handle.Init.Mode = SPI_MODE_MASTER;                         // 主机模式
    spi_handle.Init.Direction = SPI_DIRECTION_2LINES;               // 全双工
    spi_handle.Init.DataSize = SPI_DATASIZE_8BIT;                   // 8位数据
    spi_handle.Init.CLKPolarity = SPI_POLARITY_LOW;                 // 时钟极性 CPOL=0
    spi_handle.Init.CLKPhase = SPI_PHASE_1EDGE;                     // 时钟相位 CPHA=0 (模式0)
    spi_handle.Init.NSS = SPI_NSS_SOFT;                             // 软件片选
    spi_handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;  // 预分频 256
    spi_handle.Init.FirstBit = SPI_FIRSTBIT_MSB;                    // 高位在前
    spi_handle.Init.TIMode = SPI_TIMODE_DISABLE;
    spi_handle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    spi_handle.Init.CRCPolynomial = 7;
    HAL_SPI_Init(&spi_handle);
}

// SPI 底层引脚与时钟初始化 (MSP)
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
    if(hspi->Instance == SPI1)
    {
        GPIO_InitTypeDef gpio_initstruct;
    
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_SPI1_CLK_ENABLE();
        
        // PA4: 片选 (CS/NSS) - 软件控制
        gpio_initstruct.Pin=GPIO_PIN_4;
        gpio_initstruct.Mode=GPIO_MODE_OUTPUT_PP;
        gpio_initstruct.Pull=GPIO_PULLUP;
        gpio_initstruct.Speed=GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA,&gpio_initstruct);
        
        // PA5: 时钟 (SCK), PA7: 主出从入 (MOSI)
        gpio_initstruct.Pin=GPIO_PIN_5|GPIO_PIN_7;
        gpio_initstruct.Mode=GPIO_MODE_AF_PP;           // 复用推挽输出
        gpio_initstruct.Pull=GPIO_PULLUP;
        gpio_initstruct.Speed=GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA,&gpio_initstruct);
        
        // PA6: 主入从出 (MISO)
        gpio_initstruct.Pin=GPIO_PIN_6;
        gpio_initstruct.Mode=GPIO_MODE_INPUT;           // 输入模式
        gpio_initstruct.Pull=GPIO_PULLUP;
        gpio_initstruct.Speed=GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA,&gpio_initstruct);
    }
}

// W25Q128 整体初始化
void w25q128_init(void)
{
    w25q128_spi_init();
    W25Q128_CS(1);
    delay_ms(5);
}

// SPI 读写一个字节 (底层收发)
uint8_t w25q128_spi_swap_byte(uint8_t data)
{
    uint8_t recv_data = 0;
    HAL_SPI_TransmitReceive(&spi_handle, &data, &recv_data,1,1000);
    
    return recv_data;
}

// 发送写使能指令 (Write Enable)
void w25q128_write_enable(void)
{
    W25Q128_CS(0);
    w25q128_spi_swap_byte(FLASH_WriteEnable);
    W25Q128_CS(1);
}

// 读取状态寄存器1 (SR1)
uint8_t w25q128_read_sr1(void)
{
    uint8_t recv_data = 0;
    
    W25Q128_CS(0);
    
    w25q128_spi_swap_byte(FLASH_ReadStatusReg1);
    recv_data = w25q128_spi_swap_byte(FLASH_DummyByte);     // 发送哑字节以读取数据
    
    W25Q128_CS(1);
    
    return recv_data;
}


// 等待芯片空闲 (轮询 BUSY 位)
void w25q128_wait_buzy(void)
{
    uint32_t timeout = 0;
    while((w25q128_read_sr1() & 0x01) == 0x01)
    {
        timeout++;
        if(timeout > 0xFFFF) // 简单超时处理
        {
            printf("Error: SPI Flash Wait Busy Timeout!\r\n"); // 打印错误提示
            break; // 强制跳出循环，拯救程序
        }
    };
}

// 发送 24位 地址 (高位在前)
void w25q128_send_address(uint32_t address)
{
    w25q128_spi_swap_byte(address >> 16);
    w25q128_spi_swap_byte(address >> 8);
    w25q128_spi_swap_byte(address);
}

// 读取数据
// address: 起始地址, data: 数据缓冲, size: 读取长度
void w25q128_read_data(uint32_t address,uint8_t *data,uint32_t size)
{
    uint32_t i =0;
    
    W25Q128_CS(0);
    
    w25q128_spi_swap_byte(FLASH_ReadData);      // 发送读指令
    w25q128_send_address(address);              // 发送地址
    
    for(i = 0 ; i < size ; i++)
    {
        data[i] = w25q128_spi_swap_byte(FLASH_DummyByte);
    }
    W25Q128_CS(1);
}

// 页编程 (写入一页数据，最大256字节)
// 注意：写入前需确保该页已被擦除
void w25q128_write_page(uint32_t address,uint8_t *data,uint16_t size)
{
    uint16_t i =0;
    w25q128_write_enable();         // 必须先使能写
    
    W25Q128_CS(0);
    
    w25q128_spi_swap_byte(FLASH_PageProgram);       // 发送页编程指令
    w25q128_send_address(address);                  // 发送地址
    
    for(i = 0 ; i < size ; i++)
    {
        w25q128_spi_swap_byte(data[i]);
    }
    
    W25Q128_CS(1);
    
    w25q128_wait_buzy();        // 等待写入完成
}

// 扇区擦除 (4KB)
void w25q128_erase_sector(uint32_t address)
{
    w25q128_write_enable();                         //写使能
    w25q128_wait_buzy();                            //确保空闲
    W25Q128_CS(0);                                  //拉低片选
    w25q128_spi_swap_byte(FLASH_SectorErase);       //发送扇区擦除指令
    w25q128_send_address(address);                  //发送地址
    W25Q128_CS(1);                                  //拉高片选
    w25q128_wait_buzy();                            //等待擦除完成
}

// 读取芯片 ID (制造商ID + 设备ID)
uint16_t w25q128_read_id(void)
{
    uint16_t device_id = 0;
    W25Q128_CS(0);
    
    w25q128_spi_swap_byte(FLASH_ManufactDeviceID);      // 发送读ID指令
    // 发送3个字节的哑数据(地址0x000000)
    w25q128_spi_swap_byte(0x00);
    w25q128_spi_swap_byte(0x00);
    w25q128_spi_swap_byte(0x00);

    // 读取ID
    device_id = w25q128_spi_swap_byte(FLASH_DummyByte) << 8;        // 高8位
    device_id |= w25q128_spi_swap_byte(FLASH_DummyByte);            // 低8位
    
    W25Q128_CS(1);
    
    return device_id;
}
