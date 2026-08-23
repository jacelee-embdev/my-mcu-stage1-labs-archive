**English** | [简体中文](README_zh.md)

# STM32F103C8T6 Project Template

## Overview

This is a bare-metal STM32F103C8T6 project template based on the HAL library. It provides a reusable starting point for later experiments, including a 72 MHz system clock, USART1, delay functions, and an LED driver. A simple main loop verifies that the basic components work correctly.

## Features

- Configures PA4 as a push-pull output and provides LED initialization, on, off, and toggle functions.
- Configures USART1 at 115200 baud and supports `printf()` output.
- Toggles the LED once per second and sends the test string `1142!` through USART1.

## Hardware

| Module | Pin / Configuration |
|---|---|
| LED | PA4, active low |
| USART1 TX / RX | PA9 / PA10, 115200 bps |

## Quick Start

Open `Projects/MDK-ARM/STM32F103.uvprojx` in Keil MDK, build the project, and flash it to the board. After reset, the LED should toggle periodically and the test message should appear in a serial terminal.

## Key Files

- `Users/main.c`: System initialization and main loop.
- `Drivers/BSP/led/`: LED driver.
- `Drivers/SYSTEM/`: Clock, delay, UART, and other basic drivers.

