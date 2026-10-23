**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32 正交编码器测试

## 项目简介

本实验使用 STM32 定时器的硬件编码器接口读取 A/B 两相信号。定时器工作在 TI12 编码器模式，可根据两相信号的先后关系自动判断方向并累计计数，同时使用输入滤波减小毛刺影响。

## 运行效果

主循环每秒调用一次 `encoder_get_count_delta()`，读取自上次调用以来的有符号计数增量，然后将计数器清零。增量通过 115200 波特率串口以 `COUNT` 格式输出，LED 同步翻转。

正负号表示旋转方向，绝对值表示采样周期内的脉冲变化量。它还不是距离或转速，需要结合编码器线数、倍频方式、减速比和采样时间换算。

## 使用方法

把编码器 A/B 相接到工程配置的定时器输入，确保电平兼容和共地。打开 `Projects/MDK-ARM` 中的 Keil 工程编译下载，缓慢正反转编码器并观察计数符号。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
