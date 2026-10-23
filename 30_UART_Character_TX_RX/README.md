**English** | [简体中文](README_zh.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 UART Character TX/RX

## Overview

This project demonstrates single-byte USART1 interrupt reception and echo. Each received character raises the RXNE interrupt. The handler reads that byte and immediately transmits it back to the host, providing a minimal bidirectional serial test.

## Features

- Configures USART1 for 115200-8-N-1 transmit and receive.
- Uses PA9 for TX and PA10 for RX.
- Enables the RXNE interrupt and processes one byte at a time.
- Echoes every received character immediately.
- Alternates two LEDs in the main loop as a running indicator.

## Behavior

Send any character from a serial terminal and the same character is returned. This experiment has no packet framing or message protocol; it only verifies basic byte communication.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, connect a USB-to-UART adapter, then build and flash the project.

## Key Files

- `Drivers/SYSTEM/uart1/uart1.c`: USART1 setup, interrupt, and echo.
- `Users/main.c`: Initialization and LED indicator.

## License

This project is licensed under the **MIT License**. Copyright (c) 2026 JesMicro. See the [LICENSE](LICENSE) file in this project's root for the full terms. Third-party components are subject to their respective licenses.
