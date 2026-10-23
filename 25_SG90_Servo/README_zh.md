**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 SG90 舵机实验

## 项目简介

本工程使用 TIM3 通道 1 产生 SG90 舵机所需的 50 Hz PWM。PWM 从 PA6 输出，程序将目标角度换算为比较值，并按顺序控制舵机转到多个测试角度。

## 主要功能

- 配置 TIM3_CH1，PWM 周期为 20 ms。
- 提供 `set_sg90_angle()` 角度控制接口。
- 依次设置 0°、20°、40°、90° 和 180°。
- 每个角度保持约 1 秒后切换。

## 硬件说明

舵机信号线接 PA6。SG90 应使用合适的独立 5 V 电源，并与 STM32 共地，避免由 MCU 引脚或板载稳压器直接承担舵机电流。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，确认供电和信号连接后编译下载。

## 主要文件

- `Drivers/BSP/pwm_sg90/`：TIM3 PWM 与角度换算。
- `Users/main.c`：角度序列测试。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
