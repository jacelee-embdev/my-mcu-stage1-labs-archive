**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 窗口看门狗实验

## 项目简介

本工程演示窗口看门狗 WWDG。与独立看门狗不同，WWDG 只能在规定计数窗口内刷新：过早或过晚都可能导致复位。程序配置提前唤醒中断，并在回调中刷新计数器、翻转 LED2。

## 主要功能

- 设置初始计数值 `0x7F`、窗口值 `0x5F` 和 8 分频。
- 开启 WWDG 提前唤醒中断及 NVIC。
- 主循环延时约 30 ms 后刷新看门狗。
- 启动时通过 USART1 判断并打印 WWDG 复位来源。

## 运行现象

正常刷新时程序持续运行；刷新时机超出允许窗口时 MCU 会复位。提前唤醒回调还会翻转 PB9 上的 LED2。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，编译下载后修改主循环延时可测试不同刷新时机。

## 主要文件

- `Drivers/BSP/wwdg/`：WWDG、中断和刷新逻辑。
- `Users/main.c`：窗口喂狗测试。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
