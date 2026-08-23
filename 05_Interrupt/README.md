**English** | [简体中文](README_zh.md)

# STM32F103C8T6 External Interrupt Experiment

## Overview

This project demonstrates GPIO external-interrupt configuration and callback handling. PA0 is configured as a falling-edge EXTI0 input. A button event toggles LED1 in the HAL callback, while the main loop blinks LED2 independently, making the relationship between interrupt-driven and foreground code easy to observe.

## Features

- Configures PA0 with a pull-up, falling-edge EXTI0, and an NVIC priority.
- Performs simple debounce handling before toggling LED1.
- Toggles LED2 every 500 ms in the main loop.

## Hardware and Behavior

| Module | Pin |
|---|---|
| Interrupt button | PA0, active low |
| LED1 / LED2 | PB8 / PB9 |

LED2 blinks continuously. Pressing the button changes the state of LED1 once.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, then build and flash the project.

## Key Files

- `Users/main.c`: Foreground LED loop.
- `Drivers/BSP/EXTI/`: EXTI initialization and callback.

