**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 RTC 闹钟实验

## 项目简介

本工程在 RTC 时间读写基础上增加 Alarm A 中断。首次运行时设置日期时间和闹钟，RTC 到达目标时刻后进入 `RTC_Alarm_IRQHandler()`，HAL 回调通过 USART1 打印“闹钟响了”。

## 主要功能

- 使用 LSE 驱动 RTC，并通过 BKP 标记避免重复初始化。
- 首次设置时间为 2026-01-24 21:40:00。
- 设置 Alarm A 为 21:40:20，并开启 RTC Alarm 中断。
- 主循环持续读取时间并让两路 LED 交替闪烁。

## 运行说明

当前闹钟动作是串口打印，不控制蜂鸣器。若备份寄存器已有初始化标记，程序不会重新写入上述测试时间和闹钟。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，需要重新测试时先清除备份域，再编译下载并观察串口。

## 主要文件

- `Drivers/BSP/rtc/rtc.c`：RTC Alarm 配置、中断与回调。
- `Users/main.c`：首次时间和闹钟设置。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
