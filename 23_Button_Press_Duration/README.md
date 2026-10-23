**English** | [简体中文](README_zh.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 Button Press Duration

## Overview

This project measures the time between pressing and releasing a button with TIM2 input capture. A falling edge on PA1 starts the measurement and resets the counter. A rising edge captures the final value. Timer-update interrupts count overflows when the press lasts longer than one 16-bit timer period.

## Features

- Runs TIM2 at 1 MHz for 1 μs time resolution.
- Switches dynamically between falling- and rising-edge capture.
- Combines overflow count and capture value to calculate total duration.
- Prints the result as `Time: ... us` through USART1.

## Hardware and Behavior

The button uses PA1 with a pull-up input. Releasing it prints the measured press duration in microseconds.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, connect the button and serial adapter, then build and flash the project.

## Key Files

- `Drivers/BSP/ic/ic.c`: Edge capture, overflow counting, and time calculation.
- `Users/main.c`: Result polling and output.

## License

This project is licensed under the **MIT License**. Copyright (c) 2026 JesMicro. See the [LICENSE](LICENSE) file in this project's root for the full terms. Third-party components are subject to their respective licenses.
