**简体中文** | [English](README.md)

# STM32F103C8T6 ESP8266 Wi-Fi 入网

## 项目简介

本工程在 ESP8266 串口通信基础上实现 Wi-Fi 入网流程。初始化阶段依次检查 AT 通信、设置 Station 模式、选择单连接模式，并使用配置的 SSID 和密码加入无线网络。

## 主要功能

- USART2 中断接收 ESP8266 AT 响应。
- 自动重试 AT 测试、工作模式和连接模式设置。
- 发送 `AT+CWJAP` 加入指定接入点。
- 以 `WIFI GOT IP` 作为成功入网的判断依据。
- 主循环使用两路 LED 交替闪烁表示程序仍在运行。

## 配置说明

使用前在 ESP8266 驱动配置中填写自己的 Wi-Fi SSID 和密码。不要把真实密码提交到公开仓库，建议后续改为独立且被忽略的本地配置文件。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，连接 ESP8266 后编译下载，并通过 USART1 查看入网过程。

## 主要文件

- `Drivers/BSP/esp8266/`：AT 指令、入网和接收缓冲。
- `Users/main.c`：初始化与运行指示。

