**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32 4G 远程控制小车

## 项目简介

本实验把预先配置好的 4G 透传模块连接到 USART2，通过蜂窝网络传输小车控制命令和测速结果。STM32F103C8T6 在串口空闲中断中解析方向命令，并定期将测速字符串发送回远端。

## 主要功能

- `M1` 前进、`M2` 后退、`M3` 左转、`M4` 右转，其他内容停止。
- PB12 外部中断统计测速脉冲，TIM2 每 100 ms 更新一次。
- OLED 显示速度，同时通过 USART2 上报。

代码中的串口驱动目录仍命名为 `bluetooth`，实际在本工程中作为通用 USART2 透传接口使用。4G 模块的入网和服务器连接需在模块侧提前配置。

## 使用方法

确认模块电源、电平、波特率及网络连接后，再编译下载 Keil 工程。真实速度仍需按机械参数校准，测试电机时应先架空车轮。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
