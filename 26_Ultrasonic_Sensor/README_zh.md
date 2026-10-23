**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 HC-SR04 超声波测距

## 项目简介

本工程驱动 HC-SR04 超声波模块测量距离。PB6 输出约 15 μs 的 TRIG 脉冲，PB7 读取 ECHO 高电平宽度；TIM2 以 1 μs 分辨率计时，并根据声波往返时间计算厘米距离。

## 主要功能

- 初始化 HC-SR04 的 TRIG、ECHO 引脚和 TIM2。
- 测量 ECHO 脉宽并换算距离。
- 每秒通过 USART1 输出一次浮点距离结果。

## 硬件连接

| HC-SR04 | STM32 引脚 |
|---|---|
| TRIG | PB6 |
| ECHO | PB7 |

注意 HC-SR04 的 ECHO 常为 5 V 电平，应按开发板和模块情况进行电平转换或分压。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，接线后编译下载，并在 115200 波特率串口终端查看结果。

## 主要文件

- `Drivers/BSP/hcsr04/`：触发、计时和距离计算。
- `Users/main.c`：周期测量与打印。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
