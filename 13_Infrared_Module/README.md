**English** | [简体中文](README_zh.md)

# STM32F103C8T6 Infrared Sensor Experiment

## Overview

This project demonstrates external-interrupt detection for a digital infrared sensor. The sensor output is connected to PB4. A falling edge on EXTI4 records an event, and the main loop responds by lighting LED1 for two seconds.

## Features

- Configures PB4 as a pulled-up, falling-edge external-interrupt input.
- Separates interrupt detection from main-loop processing with an event flag.
- Lights the indicator LED on PB8 for approximately two seconds after detection.

## Hardware and Behavior

| Module | Pin / Configuration |
|---|---|
| Infrared sensor output | PB4, active low |
| Indicator LED | PB8 |

When the sensor detects a target and asserts its output, the LED lights briefly and then turns off automatically.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, connect the sensor, then build and flash the project. Adjust the interrupt edge and active-level check if the module uses opposite polarity.

## Key Files

- `Users/main.c`: Infrared event handling.
- `Drivers/BSP/EXTI/`: Sensor interrupt driver.

