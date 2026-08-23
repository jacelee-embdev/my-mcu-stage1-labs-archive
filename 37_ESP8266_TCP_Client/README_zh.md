**简体中文** | [English](README.md)

# STM32F103C8T6 ESP8266 TCP 客户端

## 项目简介

本工程让 ESP8266 以 Station 模式加入 Wi-Fi，并作为 TCP 客户端连接指定服务器。初始化完成后进入单连接透明传输模式，应用层可以直接通过串口向远端发送数据。

## 主要功能

- 完成 AT 测试、Station 模式和 Wi-Fi 入网。
- 使用 `AT+CIPSTART` 连接配置的服务器地址和端口。
- 设置单连接及透明传输模式。
- 提供格式化发送和接收数据接口。
- 主循环调用测试函数发送示例内容，并闪烁 LED。

## 配置说明

使用前需要设置 Wi-Fi 参数、TCP 服务器 IP 和端口。真实网络凭据不应提交到公开仓库。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，先启动可访问的 TCP 服务端，再连接 ESP8266 并下载程序。

## 主要文件

- `Drivers/BSP/esp8266/`：入网、TCP 连接和透明传输。
- `Users/main.c`：客户端测试入口。

