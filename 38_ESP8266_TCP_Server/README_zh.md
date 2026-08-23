**简体中文** | [English](README.md)

# STM32F103C8T6 ESP8266 TCP 服务器

## 项目简介

本工程将 ESP8266 配置为 SoftAP 和多连接模式，并通过 AT 指令启动 TCP 服务器。外部设备连接 ESP8266 创建的无线网络后，可以作为 TCP 客户端向模块发送数据，STM32 负责接收并通过调试串口打印。

## 主要功能

- 检查 ESP8266 AT 通信并切换到 AP 模式。
- 设置 `CIPMUX=1` 多连接模式。
- 使用 `AT+CIPSERVER=1` 启动 TCP 服务。
- 缓存并输出客户端发送的数据。
- 主循环闪烁 LED 作为运行指示。

## 运行说明

服务器网络名称、地址和端口取决于 ESP8266 当前 AT 固件及配置。测试前可先用 AT 查询命令确认 SoftAP 地址和服务参数。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，连接 ESP8266 并下载程序，再从电脑或手机建立 TCP 客户端连接。

## 主要文件

- `Drivers/BSP/esp8266/`：AP、多连接和服务器逻辑。
- `Users/main.c`：数据接收与 LED 指示。

