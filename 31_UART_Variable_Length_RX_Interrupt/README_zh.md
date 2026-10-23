**简体中文** | [English](README.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 串口不定长接收：接收中断

## 项目简介

本工程使用 USART1 RXNE 中断逐字节接收不定长数据。中断把字节写入缓冲区，主循环通过比较连续两次检查时的接收计数，判断发送是否已经暂停，并把这一段数据作为完整帧回显。

## 主要功能

- 每个接收字节由 RXNE 中断写入 128 字节缓冲区。
- 使用软件“计数不再变化”方式判断一帧结束。
- 帧完成后通过 `printf()` 输出 `recv:` 和接收字符串。
- 处理后清空缓冲区，等待下一帧。

## 运行说明

串口使用 PA9/PA10、115200-8-N-1。帧边界取决于主循环调用间隔和发送数据间隔，适合学习软件超时分帧，不是严格的通信协议。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，编译下载后发送不同长度的字符串进行测试。

## 主要文件

- `Drivers/SYSTEM/uart1/uart1.c`：中断缓存和软件分帧。
- `Users/main.c`：持续处理接收数据。

## 许可证

本项目采用 **MIT License** 开源许可证。Copyright (c) 2026 JesMicro。完整条款请参阅根目录的 [LICENSE](LICENSE) 文件。第三方组件遵循各自的许可证。
