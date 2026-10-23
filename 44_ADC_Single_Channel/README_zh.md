**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 ADC 单通道采集

## 项目简介

本工程使用 ADC1 轮询采集单路模拟电压。PA1 配置为 ADC 通道 1，程序每次通过软件触发一次 12 位转换，等待完成后读取结果，并按 3.3 V 参考电压换算成电压值。

## 主要功能

- ADC1 单通道、非连续、软件触发转换。
- 上电执行 ADC 校准，采样时间为 239.5 周期。
- 读取 PA1/ADC1_IN1 的 0–4095 原始值。
- 通过 USART1 周期输出换算后的电压。

## 运行说明

可在 PA1 接入 0–3.3 V 电位器或模拟信号。输入电压不得超出 MCU 允许范围，且需与开发板共地。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，连接模拟信号后编译下载并查看串口。

## 主要文件

- `Drivers/BSP/adc/adc.c`：ADC 初始化、通道配置和轮询读取。
- `Users/main.c`：电压换算与打印。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
