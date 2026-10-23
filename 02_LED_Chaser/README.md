**English** | [简体中文](README_zh.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 LED Chaser Experiment

## Overview

This project controls two LEDs with the STM32F103C8T6 to create a simple chaser effect. PB8 and PB9 are configured as push-pull outputs, with separate on, off, and toggle functions for each LED. The experiment is useful for practicing multi-pin GPIO initialization and basic timing control.

## Features

- Initializes PB8 and PB9 as two LED output pins.
- Controls LED1 and LED2 independently; both outputs are active low.
- Swaps the state of the two LEDs every 500 ms.

## Hardware and Behavior

| Module | Pin / Configuration |
|---|---|
| LED1 | PB8, active low |
| LED2 | PB9, active low |
| System clock | 72 MHz |

When the program runs, LED1 and LED2 light alternately every 500 ms, producing a repeating chaser pattern.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, build it, and flash the board. If the wiring or active level differs, update the pin configuration and output logic in `Drivers/BSP/led/led.c`.

## Key Files

- `Users/main.c`: Alternating LED control logic.
- `Drivers/BSP/led/`: Dual-LED driver.

## License

This project is licensed under the **MIT License**. Copyright (c) 2026 JesMicro. See the [LICENSE](LICENSE) file in this project's root for the full terms. Third-party components are subject to their respective licenses.
