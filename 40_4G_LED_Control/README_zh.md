**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 4G 模块控制 LED

## 项目简介

本工程通过 USART2 接收 E840 4G 模块透传的数据，并根据文本命令控制 LED1。接收内容包含 `ON` 时点亮 LED，包含 `OFF` 时熄灭 LED，USART1 同时输出收到的数据用于调试。

## 主要功能

- 以 115200 波特率初始化 E840 串口。
- RXNE 中断逐字节写入接收缓冲区。
- 使用软件空闲检测判断一段数据接收完成。
- 解析 `ON`、`OFF` 命令并控制 PB8 上的 LED1。

## 运行说明

本工程只实现 STM32 与已经完成网络配置的 4G 模块之间的串口透传，不包含 SIM 卡入网或服务器参数配置流程。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，先配置好 E840 的网络透传，再连接 USART2 并编译下载。

## 主要文件

- `Drivers/BSP/4G_e840/`：串口收发和缓冲区。
- `Users/main.c`：命令解析与 LED 控制。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
