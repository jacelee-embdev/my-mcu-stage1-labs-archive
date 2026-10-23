**English** | [简体中文](README_zh.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 ESP8266 TCP Server

## Overview

This project configures the ESP8266 as a SoftAP with multiple connections and starts a TCP server through AT commands. A computer or phone can join the ESP8266 network and connect as a TCP client. The STM32 receives client data and reports it through the debug UART.

## Features

- Checks ESP8266 AT communication and selects AP mode.
- Enables multiple connections with `CIPMUX=1`.
- Starts the TCP service with `AT+CIPSERVER=1`.
- Buffers and reports data received from connected clients.
- Blinks two LEDs in the main loop as a running indicator.

## Runtime Notes

The network name, address, and server port depend on the ESP8266 AT firmware and its current configuration. Query the SoftAP address and service settings before testing.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, connect the ESP8266, and flash the project. Then connect a TCP client from a computer or phone.

## Key Files

- `Drivers/BSP/esp8266/`: AP, multi-connection, and server logic.
- `Users/main.c`: Data reception and LED indication.

## License

This project is licensed under the **MIT License**. Copyright (c) 2026 JesMicro. See the [LICENSE](LICENSE) file in this project's root for the full terms. Third-party components are subject to their respective licenses.
