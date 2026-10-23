**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 ADC 多通道 DMA 采集

## 项目简介

本工程让 ADC1 以扫描模式连续采集四路模拟输入，并用 DMA 循环搬运结果。PA0–PA3 分别对应 ADC 通道 0–3，四个转换值按固定顺序写入数组，再通过 USART1 换算并打印电压。

## 主要功能

- 开启 ADC1 扫描和连续转换模式。
- 依次采集 ADC_CHANNEL_0、1、2、3。
- DMA1_Channel1 以半字循环写入四元素数组。
- 周期输出四路 0–3.3 V 换算结果。

## 硬件说明

四路输入使用 PA0、PA1、PA2、PA3。所有模拟信号必须共地并保持在 MCU ADC 允许电压范围内。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，连接模拟信号后编译下载，在串口终端查看四路电压。

## 主要文件

- `Drivers/BSP/adc/adc.c`：扫描序列和 DMA 配置。
- `Users/main.c`：四路结果输出。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
