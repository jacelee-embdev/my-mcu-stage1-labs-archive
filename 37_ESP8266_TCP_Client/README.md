**English** | [简体中文](README_zh.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 ESP8266 TCP Client

## Overview

This project joins Wi-Fi in ESP8266 Station mode and connects to a configured TCP server as a client. After connecting, it enters single-connection transparent-transmission mode so application data can be written directly through the module UART.

## Features

- Performs the AT check, Station-mode setup, and Wi-Fi join sequence.
- Uses `AT+CIPSTART` with the configured server address and port.
- Selects single-connection and transparent-transmission modes.
- Provides formatted data-send and receive helpers.
- Calls a test sender in the main loop and blinks the LEDs.

## Configuration

Set the Wi-Fi details, TCP server IP, and port before use. Keep real network credentials out of a public repository.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK. Start a reachable TCP server, connect the ESP8266, then build and flash the project.

## Key Files

- `Drivers/BSP/esp8266/`: Wi-Fi join, TCP connection, and transparent transmission.
- `Users/main.c`: Client test entry point.

## License

This project is licensed under the **MIT License**. Copyright (c) 2026 JesMicro. See the [LICENSE](LICENSE) file in this project's root for the full terms. Third-party components are subject to their respective licenses.
