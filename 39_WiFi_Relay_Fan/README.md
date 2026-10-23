**English** | [简体中文](README_zh.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 Wi-Fi Relay Fan

## Overview

This project connects the ESP8266 to a remote TCP server as a client and controls a fan relay from received text. A message containing `ON` energizes the relay, while a message containing `OFF` releases it, providing a simple Wi-Fi remote switch.

## Features

- Joins Wi-Fi and connects to a configured TCP server automatically.
- Receives remote text through single-connection transparent transmission.
- Parses `ON` and `OFF` commands.
- Drives an active-low fan relay on PB6.
- Reports network diagnostics through USART1 and alternates two status LEDs.

## Configuration and Safety

Set the local Wi-Fi details, server address, and port before use, and do not publish real passwords. Connect a fan or mains load only through a properly isolated and protected relay module.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK. Start the TCP server, connect the hardware, then build and flash the project.

## Key Files

- `Drivers/BSP/esp8266/`: Network connection and reception.
- `Drivers/BSP/relay_fan/`: Fan relay driver.

## License

This project is licensed under the **MIT License**. Copyright (c) 2026 JesMicro. See the [LICENSE](LICENSE) file in this project's root for the full terms. Third-party components are subject to their respective licenses.
