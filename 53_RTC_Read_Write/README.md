**English** | [简体中文](README_zh.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 RTC Time Read/Write

## Overview

This project uses a 32.768 kHz LSE as the RTC clock and demonstrates initial date/time setup followed by continuous reading. The value `0xA5A5` in backup register 1 marks an initialized RTC so normal resets do not overwrite the current time.

## Features

- Configures LSE, the RTC clock source, and a 1 Hz time base.
- Sets 2026-01-24 21:40:05 on first initialization.
- Uses a BKP marker to decide whether setup is required.
- Reads and prints date and time continuously through USART1.

## Runtime Notes

With backup power and an intact backup domain, the RTC continues across reset or loss of main power. Clear the backup domain or change the marker when you need to apply the test time again.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK. Confirm that the board has an LSE crystal, then build and flash the project.

## Key Files

- `Drivers/BSP/rtc/rtc.c`: RTC, LSE, time, and BKP operations.
- `Users/main.c`: First-time setup and time reading.

## License

This project is licensed under the **MIT License**. Copyright (c) 2026 JesMicro. See the [LICENSE](LICENSE) file in this project's root for the full terms. Third-party components are subject to their respective licenses.
