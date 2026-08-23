**English** | [简体中文](README_zh.md)

# STM32F103C8T6 Pulse Counter

## Overview

This project configures TIM2 in external clock mode to count pulses arriving on PA1. Falling edges on TIM2 channel 2 act as the timer clock. The main loop reads the counter register and reports a new value through USART1 whenever the count changes.

## Features

- Uses TIM2 external clock mode 1 with no prescaling.
- Increments the counter on each falling edge at PA1/TIM2_CH2.
- Uses the full 16-bit auto-reload value of 65535.
- Prints `CNT` only when the value changes, avoiding duplicate output.

## Behavior

Apply button pulses or a digital pulse source to PA1. The serial terminal displays the increasing hardware count.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK. Connect the pulse source and a common ground, then build and flash the project.

## Key Files

- `Drivers/BSP/counter/counter.c`: External clock counter and value reporting.
- `Users/main.c`: Initialization and continuous polling.

