**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 DMA 内存到外设

## 项目简介

本工程使用 DMA 把内存数据发送到 USART1，演示内存到外设传输。程序先生成一个包含 1000 个字符 `A` 的缓冲区，再由 DMA1 通道 4 将其送入串口数据寄存器，CPU 无需逐字节轮询发送。

## 主要功能

- DMA1_Channel4 关联 USART1_TX。
- 内存地址按字节自增，外设地址保持不变。
- 普通模式一次发送 1000 字节。
- 主循环在 DMA 发送后继续交替控制两路 LED。

## 运行现象

USART1 的 PA9 会连续输出 1000 个 `A`，串口参数为 115200-8-N-1。LED 闪烁说明前台代码可继续运行。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，连接串口助手后编译下载。

## 主要文件

- `Drivers/BSP/dma/dma.c`：USART1_TX DMA 配置。
- `Users/main.c`：生成并发送测试缓冲区。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
