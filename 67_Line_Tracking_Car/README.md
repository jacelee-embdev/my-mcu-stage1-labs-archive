**English** | [简体中文](README_zh.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32 Dual-Sensor Line-Tracking Car

## Overview

This experiment uses two infrared tracking sensors to detect a floor line and applies simple on/off motor control. PB13 reads the left sensor and PB14 reads the right sensor. The current driver treats a low input level as an active detection.

## Control Logic

- Both sensors active: move forward.
- Only the right sensor active: correct to the left.
- Only the left sensor active: correct to the right.
- Neither sensor active: stop.

The main loop samples the sensors about every 10 ms. This version uses fixed-speed direction control, making it useful for validating sensor polarity and the basic correction logic before adding PWM or closed-loop control.

## Usage

Adjust sensor height and sensitivity until the line and background are distinguished reliably. Open the Keil project under `Projects/MDK-ARM`, build, and flash it. If correction is reversed, check sensor placement, motor wiring, and active-level definitions.

## License

This project is licensed under the **MIT License**. Copyright (c) 2026 JesMicro. See the [LICENSE](LICENSE) file in this project's root for the full terms. Third-party components are subject to their respective licenses.
