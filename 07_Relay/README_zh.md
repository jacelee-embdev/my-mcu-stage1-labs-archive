**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 继电器实验

## 项目简介

本工程演示 STM32F103C8T6 对继电器模块的基本开关控制。PB7 被配置为推挽输出，驱动层封装了初始化、吸合、释放和状态读取接口，主循环按固定时间重复切换继电器。

## 主要功能

- 初始化 PB7 继电器控制引脚。
- 提供继电器开启、关闭和状态读取函数。
- 每隔 200 ms 切换一次继电器状态。

## 硬件与现象

| 模块 | 引脚 / 配置 |
|---|---|
| 继电器控制端 | PB7，低电平吸合 |
| 系统时钟 | 72 MHz |

运行后继电器以约 400 ms 为一个完整开关周期反复动作。实际使用时应通过合适的驱动模块连接负载，不能由 MCU 引脚直接驱动线圈。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，确认继电器模块有效电平后编译下载。

## 主要文件

- `Users/main.c`：周期控制逻辑。
- `Drivers/BSP/relay_alarm/`：继电器驱动。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
