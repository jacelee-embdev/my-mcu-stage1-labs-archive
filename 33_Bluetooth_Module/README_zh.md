**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 蓝牙串口模块实验

## 项目简介

本工程通过 USART2 与串口蓝牙模块通信，并使用 USART1 作为调试终端。程序每秒向蓝牙端发送递增的 `test N` 消息；蓝牙接收到的数据由 RXNE 中断缓存，在 IDLE 中断判定一帧结束后转发到调试串口。

## 主要功能

- USART2 以 115200 波特率连接蓝牙模块。
- 支持格式化数据发送和 128 字节接收缓冲区。
- 使用 IDLE 中断识别不定长蓝牙数据。
- 通过 USART1 打印 `bt recv:` 调试信息。

## 硬件连接

蓝牙模块使用 USART2：PA2 为 TX、PA3 为 RX；调试串口 USART1 使用 PA9/PA10。两个串口均需共地并交叉连接收发线。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，连接蓝牙模块后编译下载。

## 主要文件

- `Drivers/BSP/bluetooth/`：蓝牙串口收发。
- `Users/main.c`：周期发送测试。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
