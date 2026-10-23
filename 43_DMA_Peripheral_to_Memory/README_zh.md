**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 DMA 外设到内存

## 项目简介

本工程使用 DMA1 通道 5 将 USART1 接收数据搬运到内存缓冲区，演示外设到内存传输。初始化后调用 `HAL_UART_Receive_DMA()`，DMA 从固定的串口数据寄存器读取字节并依次写入 128 字节缓冲区。

## 主要功能

- DMA1_Channel5 关联 USART1_RX。
- 外设地址固定，内存地址逐字节递增。
- 普通模式启动一次固定长度接收。
- 主循环交替闪烁两路 LED，接收过程由 DMA 完成。

## 运行说明

当前示例重点是 DMA 接收配置；应用层没有完整的变长帧协议。可在调试器中查看 `uart1_rx_buf`，或继续补充 DMA 完成/串口空闲回调来处理数据。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，连接 USART1 后编译下载并发送测试数据。

## 主要文件

- `Drivers/BSP/dma/dma.c`：USART1_RX DMA 初始化。
- `Drivers/SYSTEM/uart1/`：接收缓冲区和串口驱动。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
