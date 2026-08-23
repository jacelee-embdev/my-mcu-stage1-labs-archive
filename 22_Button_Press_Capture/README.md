**English** | [简体中文](README_zh.md)

# STM32F103C8T6 Complete Button Capture

## Overview

This project recognizes one complete button action with TIM2 input capture. PA1 is normally pulled high. The first falling edge represents a press, after which the capture polarity changes to rising edge to wait for release. The channel then returns to falling-edge capture for the next action.

## Features

- Captures PA1 edges through TIM2_CH2.
- Changes capture polarity dynamically between falling and rising edges.
- Prints `DOWN` and `UP` for the press and release events.
- Keeps two LEDs alternating in the foreground loop.

## Behavior

After one press-and-release action, USART1 reports the two edges in order. This experiment focuses on the complete edge sequence and does not yet calculate the press duration.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK. Connect an active-low button to PA1, then build and flash the project.

## Key Files

- `Drivers/BSP/ic/ic.c`: Dual-edge capture state logic.
- `Users/main.c`: Peripheral initialization.

