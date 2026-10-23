**English** | [简体中文](README_zh.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 Touchless Trash Can

## Overview

This project combines an HC-SR04, SG90 servo, button, buzzer, and LEDs to build a simple automatic trash-can lid. Pressing Button 1 or detecting an object closer than 10 cm opens the lid for about two seconds. When no trigger remains, the lid closes automatically.

## Features

- Uses the HC-SR04 to detect a nearby user.
- Supports manual opening with a button.
- Moves the SG90 between 0° and 180° for lid control.
- Sounds a short buzzer prompt and indicates open/closed state with LEDs.
- Uses a state flag to avoid repeating the opening notification.

## Hardware Notes

The servo and ultrasonic module require adequate power, a common ground, and a safe ECHO logic level. Refer to the BSP headers for exact pins.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK. Connect the modules, verify the servo's mechanical range, then build and flash the project.

## Key Files

- `Drivers/BSP/trash_bin_ctrl_core/`: Open, close, and state logic.
- `Drivers/BSP/hcsr04/` and `pwm_sg90/`: Distance and servo drivers.

## License

This project is licensed under the **MIT License**. Copyright (c) 2026 JesMicro. See the [LICENSE](LICENSE) file in this project's root for the full terms. Third-party components are subject to their respective licenses.
