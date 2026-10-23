**English** | [简体中文](README_zh.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 Bluetooth UART Module

## Overview

This project communicates with a serial Bluetooth module through USART2 and uses USART1 as a debug console. It sends an incrementing `test N` message to the Bluetooth link every second. Received Bluetooth bytes are buffered by RXNE interrupts and forwarded to the debug UART when the IDLE interrupt marks the end of a message.

## Features

- Runs the Bluetooth UART at 115200 baud on USART2.
- Supports formatted transmission and a 128-byte receive buffer.
- Detects variable-length Bluetooth messages with the IDLE interrupt.
- Prints received content through USART1 with the `bt recv:` prefix.

## Hardware

USART2 uses PA2 for TX and PA3 for RX. The debug USART1 uses PA9/PA10. Cross the TX/RX connections and join all grounds.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, connect the Bluetooth module, then build and flash the project.

## Key Files

- `Drivers/BSP/bluetooth/`: Bluetooth UART transmit and receive.
- `Users/main.c`: Periodic transmission test.

## License

This project is licensed under the **MIT License**. Copyright (c) 2026 JesMicro. See the [LICENSE](LICENSE) file in this project's root for the full terms. Third-party components are subject to their respective licenses.
