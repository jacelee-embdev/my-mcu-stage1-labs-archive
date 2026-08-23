**简体中文** | [English](README.md)

# STM32F103C8T6 ADC 单通道 DMA 采集

## 项目简介

本工程使用 ADC1 连续采样 PA1，并通过 DMA1 通道 1 自动更新内存中的 16 位结果。DMA 采用循环模式，CPU 在主循环中可以直接读取最新采样值并换算为电压，无需逐次等待 ADC 完成。

## 主要功能

- ADC1 通道 1 连续转换，12 位右对齐。
- ADC 上电校准并使用 239.5 周期采样时间。
- DMA 半字传输、循环模式、外设到内存。
- USART1 周期打印最新电压值。

## 运行说明

模拟输入接 PA1，范围应保持在 0–3.3 V。`adc_result` 会被 DMA 持续覆盖，代表最近一次转换结果。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，连接模拟源后编译下载。

## 主要文件

- `Drivers/BSP/adc/adc.c`：ADC 与循环 DMA 配置。
- `Users/main.c`：结果读取和电压输出。

