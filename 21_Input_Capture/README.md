**English** | [简体中文](README_zh.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 Input Capture Basics

## Overview

This project demonstrates basic TIM2 input-capture configuration. PA1 is mapped to TIM2 channel 2, where a falling edge generates a capture interrupt. The callback prints `DOWN` through USART1 to confirm that the external edge was captured by the timer.

## Features

- Runs TIM2 at 1 MHz for 1 μs counter resolution.
- Captures falling edges on PA1/TIM2_CH2.
- Enables capture and update interrupts and reports the capture through UART.
- Alternates two LEDs in the main loop as a running indicator.

## Behavior

Applying a valid falling edge to PA1 prints `DOWN` on USART1. The debug UART uses PA9/PA10 at 115200 baud.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK. Connect a button or pulse source to PA1, then build and flash the project.

## Key Files

- `Drivers/BSP/ic/ic.c`: TIM2 capture and interrupt callback.
- `Users/main.c`: Initialization and running indicator.

## License

This project is licensed under the **MIT License**. Copyright (c) 2026 JesMicro. See the [LICENSE](LICENSE) file in this project's root for the full terms. Third-party components are subject to their respective licenses.
