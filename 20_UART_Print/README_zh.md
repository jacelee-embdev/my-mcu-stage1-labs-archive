**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 串口打印实验

## 项目简介

本工程演示 USART1 初始化和 `printf()` 串口重定向。程序以 115200 波特率启动串口，上电后发送一次 `Hello World!`，主循环再交替控制两路 LED，便于同时确认程序和串口均正常运行。

## 主要功能

- 配置 USART1 为 8 数据位、1 停止位、无校验。
- 将标准输出重定向到 USART1。
- 上电打印测试字符串，并让 PB8、PB9 两路 LED 每 500 ms 交替亮灭。

## 硬件连接

USART1 TX/RX 使用 PA9/PA10，串口参数为 115200-8-N-1。USB 转串口模块与开发板需要共地。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，编译下载后打开串口助手查看输出。

## 主要文件

- `Users/main.c`：打印和 LED 测试。
- `Drivers/SYSTEM/uart1/`：USART1 驱动与输出重定向。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
