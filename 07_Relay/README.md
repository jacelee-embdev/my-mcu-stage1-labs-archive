**English** | [简体中文](README_zh.md)

# STM32F103C8T6 Relay Experiment

## Overview

This project demonstrates basic relay-module control with the STM32F103C8T6. PB7 is configured as a push-pull output. The driver provides initialization, on, off, and state-reading functions, while the main loop switches the relay at a fixed interval.

## Features

- Initializes PB7 as the relay control output.
- Provides relay on, off, and status functions.
- Changes the relay state every 200 ms.

## Hardware and Behavior

| Module | Pin / Configuration |
|---|---|
| Relay control | PB7, active low |
| System clock | 72 MHz |

The relay repeats a complete on/off cycle about every 400 ms. Use a suitable relay driver module for the load; an MCU pin must not drive a relay coil directly.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK. Confirm the relay module's active level, then build and flash the project.

## Key Files

- `Users/main.c`: Periodic relay control.
- `Drivers/BSP/relay_alarm/`: Relay driver.

