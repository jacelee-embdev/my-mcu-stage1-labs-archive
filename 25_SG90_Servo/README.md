**English** | [简体中文](README_zh.md)

# STM32F103C8T6 SG90 Servo Experiment

## Overview

This project generates the 50 Hz PWM required by an SG90 servo using TIM3 channel 1. PWM is output on PA6. The driver converts a requested angle into a compare value, and the example moves the servo through several test positions.

## Features

- Configures TIM3_CH1 with a 20 ms PWM period.
- Provides `set_sg90_angle()` as an angle-based control interface.
- Commands 0°, 20°, 40°, 90°, and 180° in sequence.
- Holds each position for approximately one second.

## Hardware Notes

Connect the servo signal to PA6. Power the SG90 from a suitable external 5 V supply and connect its ground to the STM32 ground. Do not draw servo current directly from an MCU pin or an undersized board regulator.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK. Check power and signal wiring, then build and flash the project.

## Key Files

- `Drivers/BSP/pwm_sg90/`: TIM3 PWM and angle conversion.
- `Users/main.c`: Servo position sequence.

