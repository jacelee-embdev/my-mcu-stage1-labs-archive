**English** | [简体中文](README_zh.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 BKP Register Read/Write

## Overview

This project demonstrates access to the STM32F103 backup domain. It enables the PWR and BKP clocks, removes backup-domain write protection, writes `0xA5A5` to RTC backup register 1, and immediately reads the value back through USART1.

## Features

- Initializes the RTC handle and a 32.768 kHz-to-1 Hz prescaler.
- Reads and writes a selected backup register through HAL APIs.
- Writes a fixed marker and verifies the returned value.
- Alternates two LEDs in the main loop.

## Runtime Notes

Backup registers can survive loss of main power when the VBAT domain remains powered and the backup domain is not reset. They are commonly used for small flags such as “already initialized.”

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, build and flash it, then confirm the `A5A5` value in the serial terminal.

## Key Files

- `Drivers/BSP/rtc/rtc.c`: Backup-domain and register APIs.
- `Users/main.c`: Write/read test.

## License

This project is licensed under the **MIT License**. Copyright (c) 2026 JesMicro. See the [LICENSE](LICENSE) file in this project's root for the full terms. Third-party components are subject to their respective licenses.
