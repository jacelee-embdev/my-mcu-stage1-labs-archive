**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 CAN 收发实验

## 项目简介

本工程使用 CAN1 内部回环模式验证帧发送和接收，不需要第二个 CAN 节点。按下按键 1 后，程序递增 8 字节测试数据并发送扩展帧；回环数据进入 FIFO0 后被读取并通过 USART1 打印。

## 主要功能

- CAN1 配置为 `CAN_MODE_LOOPBACK`。
- 使用 32 位掩码过滤器并接收全部 ID。
- 发送扩展 ID `0x12345678`、长度 8 的数据帧。
- 打印发送和接收的每个字节。
- PA0 按键触发发送，两路 LED 指示主循环运行。

## 运行说明

当前回环测试不经过外部收发器或总线。若改为正常模式，需要核对 CAN 引脚时钟配置、位时序，并外接 CAN 收发器和终端电阻。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，编译下载后按键并查看串口收发内容。

## 主要文件

- `Drivers/BSP/can/can.c`：CAN 配置、过滤、发送与接收。
- `Users/main.c`：测试帧和按键逻辑。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
