**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 电动车报警器

## 项目简介

本工程把 433 MHz 遥控输入、振动传感器和继电器报警输出组合成一个简易电动车防盗报警器。遥控 A 键进入警戒模式，B 键解除警戒；处于警戒模式时，检测到振动便启动报警输出。

## 主要功能

- 接收遥控器的设防和撤防指令。
- 实时读取 PA4 上的低电平振动信号。
- 通过 PB7 低电平有效的继电器控制蜂鸣器或报警器。
- 封装锁车、解锁和防盗报警动作。

## 硬件连接

| 模块 | 引脚 |
|---|---|
| 遥控 A / B | PA5 / PA12 |
| 振动传感器 | PA4 |
| 报警继电器 | PB7 |

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，连接低电平有效的振动和继电器模块后编译下载。测试功率负载时应确保继电器侧供电和隔离正确。

## 主要文件

- `Users/main.c`：设防状态和报警流程。
- `Drivers/BSP/exti/`、`Drivers/BSP/relay_alarm/`：输入与报警驱动。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
