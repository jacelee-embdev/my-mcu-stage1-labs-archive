**English** | [简体中文](README_zh.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 Smoking Room Control

## Overview

This project monitors a smoking-room sensor through an analog voltage. ADC1 channel 8 continuously samples PB0 with DMA. The LCD1602 shows the current sensor voltage and alarm threshold. When the value exceeds the threshold, the system starts a fan relay and sounds the buzzer.

## Features

- Continuously samples the smoke-sensor voltage on PB0/ADC1_IN8.
- Uses two buttons to lower or raise the initial 1.0 V threshold in 0.1 V steps.
- Shows the measured value and threshold on the LCD1602.
- Turns the fan and buzzer on above the threshold and off after recovery.

## Hardware Notes

Threshold buttons use PB13/PB14. See the BSP drivers for the remaining LCD, buzzer, and relay pins. The voltage threshold is only an experiment setting; real smoke concentration requires calibration for the chosen sensor.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK. Verify the logic with a low-voltage load before connecting a fan.

## Key Files

- `Drivers/BSP/adc/`: Smoke-voltage acquisition.
- `Users/main.c`: Threshold, display, and actuator control.

## License

This project is licensed under the **MIT License**. Copyright (c) 2026 JesMicro. See the [LICENSE](LICENSE) file in this project's root for the full terms. Third-party components are subject to their respective licenses.
