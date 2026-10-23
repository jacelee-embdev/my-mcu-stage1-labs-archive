**English** | [简体中文](README_zh.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32 Jog-Controlled Car

## Overview

This experiment implements momentary, or jog, control for a two-wheel car. Each valid serial command produces a short movement of about 200 ms. The main loop then stops the motors immediately. Compared with continuous remote control, jog control is useful for observing individual actions and making small position adjustments.

## Commands

- `M1`: short forward movement.
- `M2`: short backward movement.
- `M3`: short left turn.
- `M4`: short right turn.
- Any other message: stop.

USART2 parses each message in the receive-idle interrupt. The current implementation also performs the 200 ms delay inside that interrupt, which is acceptable for this learning demo but not recommended for a production design.

## Usage

Connect a UART or Bluetooth serial link and the motor driver. Open the Keil project under `Projects/MDK-ARM`, build, and flash it. Adjust the delay to change the jog distance.

## License

This project is licensed under the **MIT License**. Copyright (c) 2026 JesMicro. See the [LICENSE](LICENSE) file in this project's root for the full terms. Third-party components are subject to their respective licenses.
