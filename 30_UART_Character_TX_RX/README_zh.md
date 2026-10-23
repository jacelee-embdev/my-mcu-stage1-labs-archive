**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 串口单字符收发

## 项目简介

本工程演示 USART1 的单字节中断接收和回显。每收到一个字符，USART1 的 RXNE 中断读取该字节并立即原样发送回上位机，实现最小的串口双向通信测试。

## 主要功能

- USART1 配置为 115200-8-N-1，支持发送和接收。
- PA9 为 TX，PA10 为 RX。
- 开启 RXNE 中断，每次处理一个字节。
- 接收到的字符立即回显。
- 主循环交替闪烁两路 LED 作为运行指示。

## 运行现象

在串口助手中发送任意单个字符，终端会收到相同字符。该实验没有数据帧或缓冲区协议，只验证最基础的字节收发。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，连接 USB 转串口模块后编译下载。

## 主要文件

- `Drivers/SYSTEM/uart1/uart1.c`：USART1 初始化、中断和回显。
- `Users/main.c`：外设初始化与 LED 指示。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
