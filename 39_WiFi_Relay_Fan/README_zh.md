**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 Wi-Fi 继电器风扇

## 项目简介

本工程使用 ESP8266 TCP 客户端连接远端服务器，并根据收到的文本命令控制风扇继电器。接收内容包含 `ON` 时吸合继电器，包含 `OFF` 时释放继电器，实现简单的 Wi-Fi 远程开关。

## 主要功能

- ESP8266 自动加入 Wi-Fi 并连接配置的 TCP 服务器。
- 使用单连接透明传输接收远端文本。
- 解析 `ON`、`OFF` 控制命令。
- PB6 低电平驱动风扇继电器。
- USART1 输出网络调试信息，两路 LED 指示运行状态。

## 配置与安全

使用前设置本地 Wi-Fi、服务器地址和端口，且不要向公开仓库提交真实密码。风扇或市电负载必须通过有隔离与保护的合格继电器模块连接。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，启动 TCP 服务端并连接硬件后编译下载。

## 主要文件

- `Drivers/BSP/esp8266/`：网络连接和数据接收。
- `Drivers/BSP/relay_fan/`：风扇继电器驱动。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
