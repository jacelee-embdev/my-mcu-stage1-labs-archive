**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 ESP8266 串口通信

## 项目简介

本工程搭建 STM32 与 ESP8266 AT 固件之间的基础串口通信。USART2 负责模块收发，驱动使用中断缓冲数据，并提供发送 AT 指令、等待指定响应和清空接收缓冲区等接口。

## 主要功能

- 以 115200 波特率初始化 ESP8266 串口。
- 逐字节中断接收模块返回数据。
- 通过软件等待判断一段响应是否接收完成。
- 周期发送 `AT` 并检查是否收到 `OK`。
- USART1 输出命令响应和测试结果。

## 硬件连接

ESP8266 使用 USART2 的 PA2/PA3，模块应使用稳定的 3.3 V 电源并与 STM32 共地。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，确认模块运行 AT 固件后编译下载，在调试串口查看测试结果。

## 主要文件

- `Drivers/BSP/esp8266/`：串口缓冲和 AT 指令接口。
- `Users/main.c`：通信测试和 LED 指示。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
