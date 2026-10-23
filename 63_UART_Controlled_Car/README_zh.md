**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32 串口控制小车

## 项目简介

本实验使用 USART2 接收上位机或其他串口设备发送的文本命令，并在空闲线中断中解析命令，控制两轮小车运动。主循环无需轮询，接收和动作处理由串口中断完成。

## 控制命令

- `M1`：前进。
- `M2`：后退。
- `M3`：左转。
- `M4`：右转。
- 其他内容：停止。

USART2 波特率为 115200，驱动目录沿用了 `bluetooth` 名称，但本工程可直接连接 USB 转串口模块进行测试。

## 使用方法

连接电机驱动和串口设备，确保双方共地及电平兼容。打开 `Projects/MDK-ARM` 中的 Keil 工程并下载，然后用串口工具发送完整命令。测试时请先架空车轮，确认方向正确后再落地运行。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
