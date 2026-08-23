**English** | [简体中文](README_zh.md)

# STM32F103C8T6 LED Experiment

## Overview

This project demonstrates basic GPIO output control on the STM32F103C8T6. PA0 is configured as a push-pull output and toggled periodically through the HAL library, causing an external LED to blink continuously. The experiment introduces GPIO clock enabling, output configuration, and simple BSP driver organization.

## Features

- Enables the GPIOA clock and initializes PA0 as an output.
- Provides functions to turn the LED on, turn it off, and toggle its state.
- Toggles the LED state every 500 ms in the main loop.

## Hardware and Behavior

| Module | Pin / Configuration |
|---|---|
| LED | PA0, active low |
| System clock | 72 MHz |

After the program is flashed and the board is reset, the LED blinks continuously with a complete on/off cycle of about one second.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, then build and flash the project. For a different board, update the LED pin and active level in `Drivers/BSP/led/led.c`.

## Key Files

- `Users/main.c`: Initializes and toggles the LED.
- `Drivers/BSP/led/`: LED GPIO driver.

