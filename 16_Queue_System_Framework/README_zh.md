**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 排队控制系统框架

## 项目简介

本工程是排队控制系统的前期框架，先完成 LED、蜂鸣器、闸机继电器、红外传感器和 LCD1602 等模块的驱动集成。主循环运行两个由 SysTick 标志触发的 LED 任务，用来验证分层结构和协作式任务框架。

## 主要内容

- 初始化系统所需的输入、显示、提示和执行模块。
- LCD1602 上电后显示两行测试字符串。
- SysTick 维护 1000 ms 和 500 ms 两个软件周期。
- `task1()`、`task2()` 分别翻转两路 LED。

## 运行说明

当前版本主要验证工程框架，各排队业务动作尚未组合成完整状态机。传感器、蜂鸣器和闸机驱动已经保留，可在此基础上继续实现人数统计、放行和报警逻辑。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，根据 `Drivers/BSP/` 中的定义接线后编译下载。

## 主要文件

- `Drivers/BSP/tasks/`：SysTick 任务框架。
- `Drivers/BSP/`：LCD、红外、蜂鸣器和闸机等驱动。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
