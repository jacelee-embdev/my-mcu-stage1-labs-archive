**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 按键按下时间测量

## 项目简介

本工程使用 TIM2 输入捕获测量按键从按下到释放的持续时间。PA1 下降沿开始计时并清零计数器，上升沿读取捕获值；若按住时间超过一次 16 位计数周期，更新中断会累计溢出次数。

## 主要功能

- TIM2 以 1 MHz 计数，时间分辨率为 1 μs。
- 动态切换下降沿和上升沿捕获。
- 结合溢出次数与捕获值计算总按压时间。
- 通过 USART1 输出 `Time: ... us`。

## 硬件与现象

按键接 PA1 并使用上拉输入。每次释放按键后，串口打印本次按住的微秒数。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，连接按键和串口后编译下载。

## 主要文件

- `Drivers/BSP/ic/ic.c`：边沿捕获、溢出累计和时间计算。
- `Users/main.c`：轮询并输出测量结果。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
