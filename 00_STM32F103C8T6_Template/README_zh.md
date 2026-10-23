**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 基础工程模板

## 项目简介

这是一个基于 STM32F103C8T6 和 HAL 库的裸机工程模板，可作为后续实验的起点。工程完成 72 MHz 系统时钟、USART1、延时函数和 LED 驱动的基础配置，并用简单循环验证各部分能够正常工作。

## 主要功能

- 将 PA4 配置为推挽输出，封装 LED 初始化、点亮、熄灭和状态翻转接口。
- 将 USART1 配置为 115200 波特率，并支持 `printf()` 输出。
- 主循环每隔 1 秒翻转一次 LED，同时通过串口发送测试字符串 `1142!`。

## 硬件连接

| 模块 | 引脚 / 配置 |
|---|---|
| LED | PA4，低电平点亮 |
| USART1 TX / RX | PA9 / PA10，115200 bps |

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/STM32F103.uvprojx`，编译并下载到开发板。复位后可观察 LED 周期翻转，并通过串口助手查看测试输出。

## 主要文件

- `Users/main.c`：系统初始化和主循环。
- `Drivers/BSP/led/`：LED 驱动。
- `Drivers/SYSTEM/`：时钟、延时和串口等基础驱动。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
