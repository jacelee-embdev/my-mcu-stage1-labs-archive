**English** | [简体中文](README_zh.md)

# STM32F103C8T6 HC-SR04 Distance Measurement

## Overview

This project drives an HC-SR04 ultrasonic module to measure distance. PB6 generates an approximately 15 μs TRIG pulse, while PB7 reads the ECHO pulse width. TIM2 measures the high-level duration with 1 μs resolution, and the program converts the round-trip time into centimeters.

## Features

- Initializes the HC-SR04 TRIG and ECHO pins and TIM2.
- Measures ECHO pulse width and calculates distance.
- Prints one floating-point distance result per second through USART1.

## Hardware

| HC-SR04 | STM32 Pin |
|---|---|
| TRIG | PB6 |
| ECHO | PB7 |

HC-SR04 ECHO is commonly a 5 V signal. Use level shifting or a voltage divider when required by the board and module.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, wire the module, then build and flash it. View results in a 115200-baud terminal.

## Key Files

- `Drivers/BSP/hcsr04/`: Triggering, timing, and distance calculation.
- `Users/main.c`: Periodic measurement and output.

