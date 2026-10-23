**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 实时时钟项目

## 项目简介

本工程把 RTC、OLED、四个按键和蜂鸣器组合成可设置的实时时钟。OLED 同时显示日期、时间和闹钟时间；按键可进入时间或闹钟设置模式、移动选中项并增减数值，选中项通过闪烁提示。

## 主要功能

- LSE 驱动 RTC，并用 BKP 标记保存首次初始化状态。
- OLED 显示年月日、时分秒和 Alarm A 时间。
- 四个按键完成设置、移位、加和减操作。
- 保存新时间或闹钟后写入 RTC。
- 闹钟中断通过串口提示，并让蜂鸣器按固定节奏鸣响。

## 运行说明

默认测试时间和闹钟只在未检测到 `0xA5A5` 标记时写入。按键连接 PA0–PA3；OLED 和蜂鸣器引脚见各 BSP 驱动。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，连接 LSE、OLED 和按键后编译下载。

## 主要文件

- `Users/main.c`：界面和设置状态流程。
- `Drivers/BSP/rtc/`、`oled/`、`key/`、`beep/`：时钟与人机接口。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
