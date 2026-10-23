**English** | [简体中文](README_zh.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 Electric Bike Alarm

## Overview

This project combines 433 MHz remote inputs, a vibration sensor, and a relay-driven alarm into a simple electric-bike security system. Remote button A arms the system and button B disarms it. While armed, a detected vibration activates the alarm output.

## Features

- Receives arm and disarm commands from the remote control.
- Monitors the active-low vibration signal on PA4.
- Drives a buzzer or alarm through an active-low relay on PB7.
- Wraps the lock, unlock, and theft-alarm sequences as separate actions.

## Hardware

| Module | Pin |
|---|---|
| Remote A / B | PA5 / PA12 |
| Vibration sensor | PA4 |
| Alarm relay | PB7 |

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK. Connect active-low sensor and relay modules, then build and flash the project. Check relay-side power and isolation before testing a powered load.

## Key Files

- `Users/main.c`: Armed state and alarm flow.
- `Drivers/BSP/exti/` and `Drivers/BSP/relay_alarm/`: Input and alarm drivers.

## License

This project is licensed under the **MIT License**. Copyright (c) 2026 JesMicro. See the [LICENSE](LICENSE) file in this project's root for the full terms. Third-party components are subject to their respective licenses.
