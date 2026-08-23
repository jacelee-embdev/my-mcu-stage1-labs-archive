**English** | [简体中文](README_zh.md)

# STM32F103C8T6 Buzzer Experiment

## Overview

This project demonstrates GPIO on/off control of an active buzzer with the STM32F103C8T6. PB5 is configured as a push-pull output and changed periodically to alternate between sound and silence. The experiment focuses on initializing a simple output device, wrapping its control functions, and using delays to produce timed behavior.

## Features

- Enables the GPIOB clock and initializes PB5 as an output.
- Provides separate functions to turn the buzzer on and off.
- Sounds the buzzer for 500 ms, silences it for 500 ms, and repeats continuously.

## Hardware and Behavior

| Module | Pin / Configuration |
|---|---|
| Active buzzer | PB5, active low |
| System clock | 72 MHz |

After flashing and resetting the board, the buzzer sounds intermittently with a complete cycle of about one second.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, then build and flash the project. If the buzzer module is active high, reverse the on and off output levels in `Drivers/BSP/BEEP/beep.c`.

## Key Files

- `Users/main.c`: Periodic buzzer control logic.
- `Drivers/BSP/BEEP/`: Buzzer GPIO driver.

