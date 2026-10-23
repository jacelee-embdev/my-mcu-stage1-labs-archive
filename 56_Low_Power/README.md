**English** | [简体中文](README_zh.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 Low-Power Modes

## Overview

This project preserves entry functions for the STM32F103 Sleep, Stop, and Standby modes and currently tests Standby with a button. LED1 indicates normal execution. Pressing Button 2 enters Standby, and a rising edge on PA0/WKUP can wake the MCU.

## Features

- Provides wrappers for Sleep, Stop, and Standby.
- Restores the 72 MHz system clock after leaving Stop mode.
- Calls Standby in the current main loop; Sleep and Stop calls remain commented examples.
- Uses PA1 to enter Standby and PA0 as the wake input.

## Runtime Notes

Standby loses most runtime state, and wakeup behaves like a restart, so code after the standby entry normally does not continue. Current measurements on a development board also include regulator, LED, and debugger consumption.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, connect the buttons, then build and flash it. Uncomment one mode at a time for comparison.

## Key Files

- `Drivers/BSP/lpwr/lpwr.c`: Low-power entry and wake configuration.
- `Users/main.c`: Button-triggered test.

## License

This project is licensed under the **MIT License**. Copyright (c) 2026 JesMicro. See the [LICENSE](LICENSE) file in this project's root for the full terms. Third-party components are subject to their respective licenses.
