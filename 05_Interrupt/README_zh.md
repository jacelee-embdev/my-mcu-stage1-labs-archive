**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 外部中断实验

## 项目简介

本工程演示 GPIO 外部中断的配置和回调处理。PA0 被配置为下降沿触发的 EXTI0 输入，按键触发后在 HAL 回调中翻转 LED1；主循环同时让 LED2 周期闪烁，用来直观看出中断与前台程序可以独立运行。

## 主要功能

- 配置 PA0 上拉输入、EXTI0 下降沿触发和 NVIC 优先级。
- 在中断回调中进行简单消抖并翻转 LED1。
- 主循环每隔 500 ms 翻转 LED2。

## 硬件与现象

| 模块 | 引脚 |
|---|---|
| 中断按键 | PA0，低电平有效 |
| LED1 / LED2 | PB8 / PB9 |

LED2 持续闪烁；按下按键时，LED1 状态改变一次。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，编译并下载到开发板。

## 主要文件

- `Users/main.c`：前台闪灯逻辑。
- `Drivers/BSP/EXTI/`：外部中断初始化与回调。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
