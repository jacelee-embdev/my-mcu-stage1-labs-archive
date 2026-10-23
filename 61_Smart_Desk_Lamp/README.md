**English** | [简体中文](README_zh.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32 Smart Desk Lamp

## Overview

This experiment combines a dimmable lamp, presence sensor, light sensor, HC-SR04 distance sensor, buzzer, OLED, buttons, and Bluetooth serial control. It is a small smart-lamp prototype that supports automatic behavior as well as local and remote control.

## Features

- Automatic, manual, and remote lighting modes.
- Automatic brightness selection based on presence and ambient light.
- Distance warning when the user sits too close to the sensor.
- Usage timer with start, stop, and reset controls.
- OLED display for distance, sitting time, and system state.

## Usage

Connect the PWM lamp output, sensors, OLED, buttons, and Bluetooth module. Open the `.uvprojx` file under `Projects/MDK-ARM`, build, and flash it. The light thresholds, distance limit, and reminder duration are demonstration values; recalibrate them for the actual sensor positions and room conditions.

## Main Code

- `Users/main.c`: mode selection and application control.
- `Drivers/BSP/`: sensor, lamp, Bluetooth, buzzer, timer, and display drivers.

## License

This project is licensed under the **MIT License**. Copyright (c) 2026 JesMicro. See the [LICENSE](LICENSE) file in this project's root for the full terms. Third-party components are subject to their respective licenses.
