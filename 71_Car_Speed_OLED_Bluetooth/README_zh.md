**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32 小车测速、OLED 与蓝牙显示

## 项目简介

本实验在小车脉冲测速基础上增加 OLED 本地显示和蓝牙串口上报。PB12 的下降沿中断累计测速脉冲，TIM2 每 100 ms 读取并清零计数，然后把结果显示在 OLED，同时通过 USART2 发送到蓝牙模块。

## 运行效果

程序启动后小车持续前进，显示和发送的格式为 `speed:xx cm/s`。当前代码直接把 100 ms 内的脉冲数当作速度值，因此单位仅是实验展示，并未完成轮径和每圈脉冲数标定。

## 使用方法

连接测速传感器、OLED、蓝牙模块及电机驱动，打开 `Projects/MDK-ARM` 中的 Keil 工程编译下载。蓝牙串口使用 115200 波特率。需要准确速度时，应先加入实际机械参数和换算系数。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
