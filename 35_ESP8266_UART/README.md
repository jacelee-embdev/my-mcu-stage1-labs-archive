**English** | [简体中文](README_zh.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 ESP8266 UART Communication

## Overview

This project establishes basic serial communication between the STM32 and ESP8266 AT firmware. USART2 handles module traffic. The driver buffers received bytes with interrupts and provides helpers for sending AT commands, waiting for an expected response, and clearing the receive buffer.

## Features

- Initializes the ESP8266 UART at 115200 baud.
- Receives module responses byte by byte through interrupts.
- Detects the end of a response with a software wait method.
- Periodically sends `AT` and checks for `OK`.
- Reports responses and test results through USART1.

## Hardware

The ESP8266 uses USART2 on PA2/PA3. Power the module from a stable 3.3 V supply and connect its ground to the STM32 ground.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK. Confirm the module runs AT firmware, then build and flash the project and watch the debug UART.

## Key Files

- `Drivers/BSP/esp8266/`: UART buffering and AT-command helpers.
- `Users/main.c`: Communication test and LED indicator.

## License

This project is licensed under the **MIT License**. Copyright (c) 2026 JesMicro. See the [LICENSE](LICENSE) file in this project's root for the full terms. Third-party components are subject to their respective licenses.
