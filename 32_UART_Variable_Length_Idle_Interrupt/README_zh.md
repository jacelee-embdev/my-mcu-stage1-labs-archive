**简体中文** | [English](README.md)

# STM32F103C8T6 串口不定长接收：空闲中断

## 项目简介

本工程使用 USART1 的 RXNE 和 IDLE 中断接收不定长数据。RXNE 中断逐字节填充缓冲区，当串口总线出现一帧时间的空闲后，IDLE 中断把当前内容视为完整数据并打印，然后清空缓冲区。

## 主要功能

- USART1 使用 PA9/PA10 和 115200-8-N-1。
- RXNE 中断负责接收字节和缓冲区溢出保护。
- IDLE 中断自动识别数据流结束。
- 收到完整数据后打印 `recv:` 并复位接收状态。

## 运行说明

主循环保持空闲，接收和分帧均在 USART1 中断中完成。与软件计数法相比，IDLE 更直接地利用了串口硬件的空闲检测能力。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，编译下载后从串口助手发送不同长度的数据。

## 主要文件

- `Drivers/SYSTEM/uart1/uart1.c`：RXNE、IDLE 中断和缓冲区。
- `Users/main.c`：最小运行入口。

