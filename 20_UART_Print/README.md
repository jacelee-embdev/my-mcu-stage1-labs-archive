**English** | [简体中文](README_zh.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 UART Print Experiment

## Overview

This project demonstrates USART1 initialization and `printf()` redirection. USART1 starts at 115200 baud and sends `Hello World!` once after startup. The main loop then alternates two LEDs, making it easy to verify both program execution and serial output.

## Features

- Configures USART1 for 8 data bits, one stop bit, and no parity.
- Redirects standard output to USART1.
- Prints a startup message and alternates the LEDs on PB8 and PB9 every 500 ms.

## Hardware

USART1 TX and RX use PA9 and PA10 with 115200-8-N-1 settings. Connect the USB-to-UART adapter and board grounds together.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, build and flash it, then open a serial terminal to view the output.

## Key Files

- `Users/main.c`: Print and LED test.
- `Drivers/SYSTEM/uart1/`: USART1 driver and output redirection.

## License

This project is licensed under the **MIT License**. Copyright (c) 2026 JesMicro. See the [LICENSE](LICENSE) file in this project's root for the full terms. Third-party components are subject to their respective licenses.
