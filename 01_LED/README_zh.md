**简体中文** | [English](README.md)

# STM32F103C8T6 LED 实验

## 项目简介

本工程演示 STM32F103C8T6 最基础的 GPIO 输出控制。程序将 PA0 配置为推挽输出，通过 HAL 库周期性翻转引脚电平，使外接 LED 持续闪烁。该实验适合用于熟悉 GPIO 时钟使能、输出模式配置和简单 BSP 驱动封装。

## 主要功能

- 初始化 GPIOA 时钟和 PA0 输出引脚。
- 提供 LED 点亮、熄灭和状态翻转函数。
- 主循环每隔 500 ms 翻转一次 LED 状态。

## 硬件与现象

| 模块 | 引脚 / 配置 |
|---|---|
| LED | PA0，低电平点亮 |
| 系统时钟 | 72 MHz |

程序下载并复位后，LED 以约 1 秒为一个完整明暗周期持续闪烁。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，完成编译和下载。若使用不同开发板，只需在 `Drivers/BSP/led/led.c` 中调整 LED 引脚和有效电平。

## 主要文件

- `Users/main.c`：初始化并周期性翻转 LED。
- `Drivers/BSP/led/`：LED GPIO 驱动。

