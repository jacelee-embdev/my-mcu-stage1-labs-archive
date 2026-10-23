**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 LCD1602 单字符显示

## 项目简介

本工程实现 LCD1602 的 8 位并行驱动，并演示在指定位置显示单个字符。数据总线使用 PA0–PA7，PB1、PB2、PB10 分别连接 RS、RW、EN 控制信号；初始化后向显示屏写入字符 `L`。

## 主要功能

- 按 LCD1602 上电时序完成初始化、清屏和显示模式设置。
- 区分指令写入与字符数据写入。
- 支持通过显示地址指定字符位置。
- 主循环中的两路 LED 同时交替闪烁，作为运行指示。

## 硬件连接

| LCD1602 信号 | STM32 引脚 |
|---|---|
| D0–D7 | PA0–PA7 |
| RS / RW / EN | PB1 / PB2 / PB10 |

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，按引脚表接线并下载程序。LCD 对比度端仍需按模块要求外接电位器。

## 主要文件

- `Drivers/BSP/lcd1602/`：并行显示驱动。
- `Users/main.c`：字符显示示例。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
