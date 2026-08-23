**English** | [简体中文](README_zh.md)

# STM32F103C8T6 Custom Delay Functions

## Overview

This project explores how to implement blocking delays directly with the Cortex-M3 SysTick timer. The code configures the reload, current-value, and control registers to provide microsecond, millisecond, and second delays, and it replaces the HAL implementation of `HAL_Delay()`.

## Main Topics

- `delay_us()` converts time into SysTick counts for a 72 MHz clock.
- `delay_ms()` and `delay_s()` build longer delays from the microsecond routine.
- The CPU busy-waits during each delay, which is suitable for simple bare-metal experiments.

## Runtime Notes

The current `main.c` only initializes HAL and the 72 MHz system clock; its loop is empty. The project preserves the low-level delay implementation rather than a finished visual demo. To test it, add a GPIO toggle and control its interval with `delay_ms()`.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, then build, flash, or inspect the SysTick registers while stepping through the code.

## Key Files

- `Drivers/SYSTEM/delay/delay.c`: Custom delay implementation.
- `Users/main.c`: Minimal entry point.

