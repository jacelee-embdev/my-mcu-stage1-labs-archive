**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32 蓝牙控制小车

## 项目简介

本实验在串口控制小车的基础上接入蓝牙串口模块。手机端发送文本命令后，STM32F103C8T6 通过 USART2 的接收和空闲线中断取得一帧数据，并立即控制左右电机。

## 控制命令

- `M1`：前进。
- `M2`：后退。
- `M3`：左转。
- `M4`：右转。
- 其他内容：停止。

串口波特率为 115200。命令采用简单字符串，适合用蓝牙调试助手验证无线透传和小车方向控制。

## 使用方法

将蓝牙模块连接到 USART2，并确认模块工作电平、波特率和手机端换行设置。打开 `Projects/MDK-ARM` 中的 Keil 工程编译下载。首次运行应架空车轮，同时准备随时断开电机电源。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
