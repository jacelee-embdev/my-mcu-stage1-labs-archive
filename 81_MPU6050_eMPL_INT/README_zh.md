**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# MPU6050 eMPL/DMP 中断读取

## 项目简介

本实验在 eMPL/DMP 姿态解算基础上加入 MPU6050 数据就绪外部中断。STM32F103C8T6 将传感器 INT 引脚配置为上升沿 EXTI，由中断事件触发 DMP 数据读取，而不是在主循环中持续轮询。

## 运行效果

外部中断回调读取 `pitch`、`roll` 和 `yaw`，并通过软件计数降低串口打印频率。主循环只负责每 500 ms 翻转 LED 和输出心跳文字，因此本实验重点是验证 INT 引脚、EXTI 和 DMP 数据同步。

当前实现仍在中断回调内执行 DMP 读取和串口输出，适合学习验证；更稳健的工程应只在中断中置标志，再由主循环处理耗时操作。

## 使用方法

除 I2C 外还需连接 MPU6050 INT 引脚。打开 `Projects/MDK-ARM` 中的 Keil 工程编译下载，用串口观察姿态输出和心跳。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
