**English** | [简体中文](README_zh.md)

# STM32F103C8T6 Vibration-Triggered LED

## Overview

This project uses a vibration sensor to trigger an LED and demonstrates how an external interrupt can pass an event to the main loop through a flag. The sensor signal is connected to PA4. The interrupt records a falling edge, and the main loop performs the longer LED action outside the ISR.

## Features

- Configures PA4 as a falling-edge EXTI4 input.
- Transfers sensor events from the interrupt to the main loop with a flag.
- Lights the LED on PB8 for approximately two seconds after vibration is detected.

## Hardware and Behavior

| Module | Pin / Configuration |
|---|---|
| Vibration sensor | PA4, active low |
| Indicator LED | PB8, active low |

Triggering the sensor lights the LED for two seconds before it turns off automatically.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, connect the sensor, then build and flash the project.

## Key Files

- `Users/main.c`: Event processing and timed LED control.
- `Drivers/BSP/EXTI/`: Vibration interrupt and event flag.

