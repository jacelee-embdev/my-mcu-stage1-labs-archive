**English** | [简体中文](README_zh.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 System-Tick-Compatible Delay

## Overview

This project improves the SysTick delay method so it can work while SysTick is already running as the system time base. Instead of reloading or stopping the timer, it repeatedly reads the down-counter and accumulates elapsed cycles, preserving the existing tick configuration.

## Main Topics

- Implements microsecond busy-waiting for a 72 MHz clock.
- Handles counter wraparound when SysTick reloads.
- Builds millisecond, second, and `HAL_Delay()` functions on top of `delay_us()`.
- Includes a two-LED example for checking the delay routine.

## Runtime Notes

The loop sets LED1 on and LED2 off, waits 500 ms, and then swaps them. The second delay is currently commented out, so the two states do not have equal durations. This experiment focuses on the delay algorithm, not on a complete task scheduler.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, build and flash it, then observe the LEDs or inspect the SysTick counter in the debugger.

## Key Files

- `Drivers/SYSTEM/delay/delay.c`: Delay compatible with a running SysTick.
- `Users/main.c`: LED test entry point.

## License

This project is licensed under the **MIT License**. Copyright (c) 2026 JesMicro. See the [LICENSE](LICENSE) file in this project's root for the full terms. Third-party components are subject to their respective licenses.
