**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32 Wi-Fi 小车控制与测速上报

## 项目简介

本实验通过 ESP8266 建立网络透传连接，实现小车远程方向控制和测速数据上报。STM32F103C8T6 接收服务器文本命令控制电机，同时统计 PB12 的测速脉冲，并在 OLED 与网络端输出结果。

## 控制与上报

- `M1`、`M2`、`M3`、`M4` 分别对应前进、后退、左转和右转，其他内容停止。
- TIM2 每 100 ms 处理一次脉冲计数。
- 速度字符串显示在 OLED，并由 ESP8266 发送到远端。

当前 `cm/s` 数值仍需依据轮径和每圈脉冲数校准。

## 使用方法

打开 `Projects/MDK-ARM` 中的 Keil 工程，填写与实际网络环境相匹配的 Wi-Fi、服务器地址和端口，然后编译下载。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
