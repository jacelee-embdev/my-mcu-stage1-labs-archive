**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 独立看门狗实验

## 项目简介

本工程演示独立看门狗 IWDG 的初始化、刷新和复位来源判断。IWDG 使用内部低速时钟独立运行；主循环每 100 ms 刷新一次计数器，正常情况下不会复位，停止喂狗后则会在超时后重新启动 MCU。

## 主要功能

- 使用 64 分频和重装值 625 初始化 IWDG。
- 通过 `HAL_IWDG_Refresh()` 喂狗。
- 启动时检查 IWDG 复位标志，并通过 USART1 打印复位原因。
- 保留注释测试代码，可故意延时验证看门狗复位。

## 运行说明

当前代码持续正常喂狗并打印成功提示。若注释喂狗或加入超过超时时间的阻塞，系统将由 IWDG 复位。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，编译下载后在串口终端观察复位信息。

## 主要文件

- `Drivers/BSP/iwdg/`：IWDG 初始化与刷新。
- `Users/main.c`：复位判断和喂狗测试。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
