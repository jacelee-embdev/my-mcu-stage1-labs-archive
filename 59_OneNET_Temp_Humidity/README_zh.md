**简体中文** | [English](README.md)

# STM32F103C8T6 温湿度上传 OneNET

## 项目简介

本工程通过 DHT11 采集温湿度，使用 ESP8266 建立网络连接，并以 MQTT 协议向 OneNET 发布属性数据。程序将传感器结果封装成 JSON，约每 3 秒上传一次，同时发送 MQTT 心跳维持连接。

## 主要功能

- 从 PA5 上的 DHT11 读取温度和相对湿度。
- ESP8266 加入 Wi-Fi 并连接配置的 MQTT 服务。
- 手动构造 MQTT CONNECT、PUBLISH 和心跳数据包。
- 按 OneNET 属性格式上传 `CurrentTemperature` 和 `CurrentHumidity`。
- USART1 输出连接、测量和上传调试信息。

## 配置与安全

运行前需要根据自己的网络和 OneNET 设备填写 Wi-Fi、产品、设备及 MQTT 参数；仓库中的示例配置不能直接用于连接个人平台。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，完成 OneNET 设备配置并连接模块后编译下载。

## 主要文件

- `Drivers/BSP/dht11/`：温湿度采集。
- `Drivers/BSP/esp8266/`、`onenet/`：网络连接与 MQTT 报文。
