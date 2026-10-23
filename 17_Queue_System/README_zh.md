**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 排队控制系统

## 项目简介

本工程实现一个简易分批通行控制系统。红外传感器统计通行人数，LCD1602 显示当前状态和人数；每通过 5 人后闸机关闭并进入 5 秒等待状态，随后自动恢复通行。等待期间若传感器仍被触发，蜂鸣器执行报警节奏。

## 主要功能

- `PASS` 状态打开闸机并统计人数。
- 达到 5 人后切换到 `WAIT` 状态并关闭闸机。
- LCD1602 显示 `PASS`、`WAIT` 和人数进度。
- 两路 LED 指示不同状态，蜂鸣器提示异常通行。
- 使用 SysTick 计数和前台任务轮询组织各项功能。

## 硬件模块

红外传感器接 PB4，闸机继电器接 PB6，蜂鸣器接 PB5，LCD1602 使用并行接口。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，连接各模块后编译下载。可在 `tasks.c` 中调整每批人数和等待时间。

## 主要文件

- `Drivers/BSP/tasks/tasks.c`：系统状态、计数和任务逻辑。
- `Drivers/BSP/exti/`、`lcd1602/`、`relay_gate/`、`beep/`：外设驱动。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
