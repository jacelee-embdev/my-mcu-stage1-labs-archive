**English** | [简体中文](README_zh.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 Smart Access Control

## Overview

This project combines a matrix keypad, OLED, W25Q128, relay lock, and buzzer into a password access-control prototype. On first use, a password is stored in Flash. Later input is submitted with `#`; a valid password opens the lock briefly, while invalid attempts show an error and increase a failure counter.

## Features

- Accepts password input from a 4×4 keypad and displays prompts on the OLED.
- Stores up to ten password bytes in W25Q128 sector 0.
- Uses `#` to submit for unlocking and `*` to verify the old password before changing it.
- Operates the relay lock and buzzer after success; three consecutive failures trigger an alarm.

## Runtime Notes

This is a learning prototype. Password comparison, plaintext storage, and error handling have not been security audited and are unsuitable for real access control. Rewriting sector 0 destroys previous data there.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK. Test the relay with a safe low-voltage load before connecting a lock actuator.

## Key Files

- `Drivers/BSP/password/`: Password input, storage, and validation flow.
- `Drivers/BSP/keyboard/`, `oled/`, `relay_lock/`, and `w25q128/`: Peripheral drivers.

## License

This project is licensed under the **MIT License**. Copyright (c) 2026 JesMicro. See the [LICENSE](LICENSE) file in this project's root for the full terms. Third-party components are subject to their respective licenses.
