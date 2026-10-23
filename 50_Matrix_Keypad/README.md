**English** | [简体中文](README_zh.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 4×4 Matrix Keypad

## Overview

This project drives a 4×4 matrix keypad. During idle time, the four rows are falling-edge interrupt inputs and the four columns are low outputs. When a row triggers, the code temporarily reverses the GPIO directions, scans the columns, and maps the position to `0–9`, `A–D`, `*`, or `#`.

## Features

- Uses external interrupts to detect activity on any row.
- Performs 10 ms software debounce and row/column scanning.
- Stores one key in a small buffer for the main loop to read and clear.
- Prints the key through USART1 and flashes LED1 briefly.

## Hardware

Rows use PB0, PB1, PB2, and PB10. Columns use PB11, PB12, PB13, and PB14.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, connect the keypad in the correct row/column order, then build and flash it.

## Key Files

- `Drivers/BSP/keyboard/keyboard.c`: Interrupts, scanning, and key mapping.
- `Users/main.c`: Key reporting.

## License

This project is licensed under the **MIT License**. Copyright (c) 2026 JesMicro. See the [LICENSE](LICENSE) file in this project's root for the full terms. Third-party components are subject to their respective licenses.
