**简体中文** | [English](README.md)

# STM32F103C8T6 W25Q128 读写实验

## 项目简介

本工程通过 SPI1 驱动 W25Q128 NOR Flash，演示读取设备 ID、扇区擦除、页编程和数据读取。程序擦除地址 `0x000000` 所在扇区，写入四个测试字节，再读回并通过 USART1 打印。

## 主要功能

- SPI1 与独立片选控制 W25Q128。
- 读取制造商/设备 ID。
- 支持 4 KB 扇区擦除、最多 256 字节页写入和连续读取。
- 写入 `AA BB CC DD` 并校验读回结果。

## 硬件与数据安全

SPI1 通常使用 PA5/PA6/PA7，片选使用 PA4。程序上电会擦除 Flash 的第 0 扇区，其中已有的数据将丢失，测试前请确认该区域没有需要保留的内容。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，连接 3.3 V Flash 后编译下载。

## 主要文件

- `Drivers/BSP/w25q128/`：SPI Flash 指令和读写接口。
- `Users/main.c`：擦写验证流程。

