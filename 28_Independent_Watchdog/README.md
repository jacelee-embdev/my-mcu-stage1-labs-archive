**English** | [简体中文](README_zh.md)

# STM32F103C8T6 Independent Watchdog

## Overview

This project demonstrates IWDG initialization, refresh, and reset-source detection. The independent watchdog runs from its own low-speed clock. The main loop refreshes it every 100 ms, preventing reset during normal operation. If refreshing stops, the MCU restarts after the watchdog timeout.

## Features

- Initializes IWDG with prescaler 64 and reload value 625.
- Refreshes the counter through `HAL_IWDG_Refresh()`.
- Checks the IWDG reset flag at startup and prints the reset source through USART1.
- Includes commented test code that can intentionally cause a watchdog reset.

## Behavior

The current code feeds the watchdog continuously and prints a success message. Removing the refresh or adding a delay longer than the timeout causes an IWDG reset.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, build and flash it, then view the reset messages in a serial terminal.

## Key Files

- `Drivers/BSP/iwdg/`: IWDG initialization and refresh.
- `Users/main.c`: Reset detection and feed test.

