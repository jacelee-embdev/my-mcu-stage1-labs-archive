**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 蜂鸣器实验

## 项目简介

本工程演示 STM32F103C8T6 对有源蜂鸣器的 GPIO 开关控制。程序将 PB5 配置为推挽输出，通过周期性改变引脚电平，让蜂鸣器交替鸣响和静音。该实验主要用于熟悉简单输出设备的初始化、控制接口封装和延时控制。

## 主要功能

- 初始化 GPIOB 时钟和 PB5 输出引脚。
- 封装蜂鸣器开启和关闭函数。
- 主循环保持鸣响 500 ms，再静音 500 ms，持续重复。

## 硬件与现象

| 模块 | 引脚 / 配置 |
|---|---|
| 有源蜂鸣器 | PB5，低电平开启 |
| 系统时钟 | 72 MHz |

程序下载并复位后，蜂鸣器以约 1 秒为一个完整周期断续鸣响。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，编译并下载到开发板。若蜂鸣器模块为高电平有效，应在 `Drivers/BSP/BEEP/beep.c` 中对调开启和关闭时的输出电平。

## 主要文件

- `Users/main.c`：蜂鸣器周期控制逻辑。
- `Drivers/BSP/BEEP/`：蜂鸣器 GPIO 驱动。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
