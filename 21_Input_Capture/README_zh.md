**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 输入捕获基础实验

## 项目简介

本工程演示 TIM2 输入捕获的基本配置。PA1 映射到 TIM2 通道 2，通道检测下降沿并触发捕获中断；回调函数通过 USART1 打印 `DOWN`，用于确认外部边沿已经被定时器捕获。

## 主要功能

- 将 TIM2 配置为 1 MHz 计数，计数分辨率为 1 μs。
- 配置 TIM2_CH2 在 PA1 捕获下降沿。
- 开启捕获和更新中断，并在捕获回调中打印提示。
- 主循环交替闪烁两路 LED 作为运行指示。

## 运行现象

向 PA1 输入一个有效下降沿后，串口输出 `DOWN`。USART1 使用 PA9/PA10 和 115200 波特率。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，连接按键或脉冲源后编译下载。

## 主要文件

- `Drivers/BSP/ic/ic.c`：TIM2 输入捕获与中断回调。
- `Users/main.c`：初始化和运行指示。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
