**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 低功耗模式实验

## 项目简介

本工程保存 STM32F103 的 Sleep、Stop 和 Standby 三种低功耗入口，并使用按键测试待机模式。主循环让 LED1 作为运行指示；检测到按键 2 后进入 Standby，PA0/WKUP 的上升沿可唤醒芯片。

## 主要功能

- 提供 Sleep、Stop 和 Standby 三种封装函数。
- Stop 唤醒后重新配置 72 MHz 系统时钟。
- 当前主循环实际调用 Standby 模式，Sleep 和 Stop 调用被注释保留。
- PA1 按键进入待机，PA0 作为唤醒输入。

## 运行说明

进入 Standby 后大部分状态丢失，唤醒效果相当于重新启动程序；因此待机入口之后的 LED 代码通常不会继续执行。电流测量时需考虑开发板稳压器、指示灯和调试器自身功耗。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，连接按键并编译下载。逐项取消注释可分别测试三种模式。

## 主要文件

- `Drivers/BSP/lpwr/lpwr.c`：低功耗入口和唤醒配置。
- `Users/main.c`：按键触发测试。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
