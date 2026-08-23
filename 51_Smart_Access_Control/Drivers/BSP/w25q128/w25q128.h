#ifndef __W25Q28_H__
#define __W25Q28_H__

#include "sys.h"

/* * W25Q128 片选控制宏 (CS)
 * x=1: 拉高 (取消选中)
 * x=0: 拉低 (选中芯片)
 * 使用 do-while(0) 保证宏在 if-else 语句中的安全性
 */
#define W25Q128_CS(x)   do{ x ? \
                                HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET): \
                                HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET); \
                          }while(0)
/* 指令表 */
#define FLASH_ManufactDeviceID                  0x90    // 读制造商/设备ID
#define FLASH_WriteEnable                       0x06    // 写使能
#define FLASH_ReadStatusReg1                    0x05    // 读状态寄存器1
#define FLASH_ReadData                          0x03    // 读取数据
#define FLASH_PageProgram                       0x02    // 页编程 (写数据)
#define FLASH_SectorErase                       0x20    // 扇区擦除 (4KB)
#define FLASH_DummyByte                         0xFF    // 哑字节 (用于产生时钟以读取数据)

/* 函数声明 */
void w25q128_init(void);                                                        // 初始化
void w25q128_read_data(uint32_t address,uint8_t *data,uint32_t size);           // 读取数据
void w25q128_write_page(uint32_t address,uint8_t *data,uint16_t size);          // 页写入 (Max 256 Bytes)
void w25q128_erase_sector(uint32_t address);                                    // 扇区擦除
uint16_t w25q128_read_id(void);                                                 // 读取ID
uint8_t w25q128_spi_swap_byte(uint8_t data);                                    // SPI 底层交换字节

#endif
