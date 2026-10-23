**English** | [简体中文](README_zh.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 OneNET Temperature/Humidity Upload

## Overview

This project reads temperature and humidity from a DHT11, connects through an ESP8266, and publishes property data to OneNET with MQTT. Sensor values are encoded as JSON and uploaded approximately every three seconds, followed by an MQTT keepalive packet.

## Features

- Reads temperature and relative humidity from a DHT11 on PA5.
- Uses the ESP8266 to join Wi-Fi and reach the configured MQTT service.
- Builds MQTT CONNECT, PUBLISH, and keepalive packets in the application.
- Publishes `CurrentTemperature` and `CurrentHumidity` in OneNET property format.
- Reports connection, measurement, and upload status through USART1.

## Configuration and Security

Before running the project, enter the Wi-Fi, product, device, and MQTT settings for your own network and OneNET device. The archived example configuration cannot connect directly to a personal platform account.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK. Configure the OneNET device, connect the modules, then build and flash the project.

## Key Files

- `Drivers/BSP/dht11/`: Sensor acquisition.
- `Drivers/BSP/esp8266/` and `onenet/`: Networking and MQTT packets.

## License

This project is licensed under the **MIT License**. Copyright (c) 2026 JesMicro. See the [LICENSE](LICENSE) file in this project's root for the full terms. Third-party components are subject to their respective licenses.
