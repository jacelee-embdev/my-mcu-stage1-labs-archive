**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# MPU6050 eMPL/DMP 姿态解算

## 项目简介

本实验移植 MPU6050 的 eMPL/DMP 支持代码，由传感器内部 DMP 处理运动数据，并在 STM32F103C8T6 主循环中轮询 FIFO，取得俯仰角、横滚角和偏航角。

## 运行效果

初始化过程唤醒 MPU6050 并加载 DMP 固件。主循环每 5 ms 尝试读取一组姿态数据，以便及时清空 FIFO；读取成功约 100 次后，通过串口打印一次 `pitch`、`roll`、`yaw`，并翻转 LED 作为心跳指示。

偏航角会受陀螺仪漂移影响，本工程没有磁力计绝对航向校正。安装方向、静态零偏和震动都会影响结果。

## 使用方法

稳定连接 MPU6050，打开 `Projects/MDK-ARM` 中的 Keil 工程编译下载，并以 115200 波特率查看姿态数据。上电时保持模块静止，避免阻塞主循环导致 FIFO 溢出。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
