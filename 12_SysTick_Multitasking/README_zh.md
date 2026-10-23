**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 SysTick 模拟多任务

## 项目简介

本工程使用 1 ms SysTick 节拍和任务标志位模拟简单的协作式多任务。中断函数只负责累计时间并置位标志，主循环不断轮询任务函数，从而让两路 LED 按不同周期独立翻转。

## 主要功能

- SysTick 中断维护两组软件计数器。
- 任务 1 约每 1000 ms 翻转 LED1。
- 任务 2 约每 500 ms 翻转 LED2。
- 任务逻辑在主循环执行，避免在中断中处理较长业务。

## 运行现象

PB8 和 PB9 上的两路 LED 以不同频率闪烁，展示基于系统节拍的非阻塞定时思想。本工程不是 RTOS，不包含抢占、优先级或任务栈。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，编译下载后观察两路 LED。

## 主要文件

- `Drivers/BSP/tasks/tasks.c`：计时、标志位和任务函数。
- `Users/main.c`：协作式任务轮询。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
