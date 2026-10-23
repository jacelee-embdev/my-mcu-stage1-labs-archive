**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32 PWM 循迹小车

## 项目简介

本实验在双路红外循迹的基础上加入左右轮 PWM 调速。STM32F103C8T6 读取两个循迹传感器后，通过关闭一侧或同时驱动两侧电机来修正方向，便于比较固定方向控制与 PWM 控速的区别。

## 控制逻辑

- 两路都有效：左右轮均以比较值 95 前进。
- 一侧丢线：停止对应侧车轮，另一侧保持运行以完成转向。
- 两路都无效：两轮停止。

当前 PWM 频率约为 500 Hz，主循环每 10 ms 更新一次。比较值和传感器有效电平都是实验参数。

## 使用方法

接好循迹模块、电机驱动及 PWM 使能端，打开 `Projects/MDK-ARM` 中的 Keil 工程编译下载。通过调整 PWM 比较值、传感器间距和安装高度改善循迹效果。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
