**简体中文** | [English](README.md)

# STM32F103C8T6 按键实验

## 项目简介

本工程演示按键轮询检测和 GPIO 输出控制。PA0、PA1 接入两个低电平有效按键，程序通过软件延时完成简单消抖，并根据按键编号分别翻转 PB8、PB9 上的 LED。

## 主要功能

- 初始化两路按键输入和两路 LED 输出。
- `KeyScan()` 返回按键编号，实现统一的按键扫描接口。
- 按键 1 控制 LED1，按键 2 控制 LED2。

## 硬件与现象

| 模块 | 引脚 / 配置 |
|---|---|
| 按键 1 / 2 | PA0 / PA1，低电平有效 |
| LED1 / LED2 | PB8 / PB9，低电平点亮 |

每次检测到有效按键动作，对应 LED 的亮灭状态翻转一次。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，编译并下载。按键模块应与程序中的上拉输入和有效电平保持一致。

## 主要文件

- `Users/main.c`：按键扫描和 LED 控制逻辑。
- `Drivers/BSP/KEY/`、`Drivers/BSP/LED/`：按键与 LED 驱动。

