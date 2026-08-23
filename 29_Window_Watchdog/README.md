**English** | [简体中文](README_zh.md)

# STM32F103C8T6 Window Watchdog

## Overview

This project demonstrates the WWDG window watchdog. Unlike IWDG, WWDG must be refreshed within an allowed counter window; refreshing too early or too late can reset the MCU. The code enables the early-wakeup interrupt and refreshes the watchdog in its callback while toggling LED2.

## Features

- Uses initial counter `0x7F`, window value `0x5F`, and prescaler 8.
- Enables the WWDG early-wakeup interrupt and NVIC channel.
- Refreshes the watchdog after an approximately 30 ms foreground delay.
- Detects and prints the WWDG reset source through USART1 at startup.

## Behavior

The program runs continuously when refresh timing is valid. A refresh outside the allowed window resets the MCU. The early-wakeup callback also toggles LED2 on PB9.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, build and flash it, then change the loop delay to test different refresh timings.

## Key Files

- `Drivers/BSP/wwdg/`: WWDG, interrupt, and refresh logic.
- `Users/main.c`: Window refresh test.

