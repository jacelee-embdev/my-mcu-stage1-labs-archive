**English** | [简体中文](README_zh.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 PWM Breathing LED

## Overview

This project outputs PWM from TIM4 channel 3 and gradually changes the duty cycle to create a breathing-light effect. PB8 is configured as an alternate-function push-pull output, and the main loop controls pulse width by updating the compare register.

## Features

- Outputs PWM from TIM4_CH3 on PB8.
- Uses a prescaler of 71 and an auto-reload value of 499, producing approximately 2 kHz PWM.
- Moves the compare value between 0 and 299 with a 10 ms delay per step.
- Provides `set_pwm_compare()` for dynamic duty-cycle updates.

## Behavior

The active-low LED connected to PB8 repeatedly brightens and dims. One rise-and-fall sequence takes about six seconds. The visible brightness range depends on the compare limits and LED driver circuit.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, then build and flash the project. Adjust the compare range or step delay to change the brightness range or breathing speed.

## Key Files

- `Drivers/BSP/pwm_led/`: TIM4 PWM driver.
- `Users/main.c`: Duty-cycle ramp logic.

## License

This project is licensed under the **MIT License**. Copyright (c) 2026 JesMicro. See the [LICENSE](LICENSE) file in this project's root for the full terms. Third-party components are subject to their respective licenses.
