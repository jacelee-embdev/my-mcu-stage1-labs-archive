**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 LED 流水灯实验

## 项目简介

本工程使用 STM32F103C8T6 控制两路 LED 交替亮灭，实现简单的流水灯效果。程序将 PB8 和 PB9 配置为推挽输出，并分别封装两路 LED 的点亮、熄灭和翻转接口，用于练习多路 GPIO 的初始化与时序控制。

## 主要功能

- 同时初始化 PB8 和 PB9 两个 LED 输出引脚。
- 分别控制 LED1 和 LED2，两个 LED 均为低电平点亮。
- 每隔 500 ms 交换两路 LED 的亮灭状态。

## 硬件与现象

| 模块 | 引脚 / 配置 |
|---|---|
| LED1 | PB8，低电平点亮 |
| LED2 | PB9，低电平点亮 |
| 系统时钟 | 72 MHz |

程序运行后，LED1 与 LED2 每隔 500 ms 交替点亮，形成循环流水效果。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，编译并下载到开发板。实际接线或有效电平不同时，可修改 `Drivers/BSP/led/led.c` 中的引脚配置和控制逻辑。

## 主要文件

- `Users/main.c`：两路 LED 的交替控制逻辑。
- `Drivers/BSP/led/`：双路 LED 驱动。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
