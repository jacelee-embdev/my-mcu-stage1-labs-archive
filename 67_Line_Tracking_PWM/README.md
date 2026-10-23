**English** | [简体中文](README_zh.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32 PWM Line-Tracking Car

## Overview

This experiment adds independent wheel PWM to a two-sensor infrared line tracker. The STM32F103C8T6 reads both tracking sensors and either drives both wheels or stops one wheel to correct the direction. It is useful for comparing simple direction-only tracking with PWM-based motor control.

## Control Logic

- Both sensors active: both wheel compare values are set to 95.
- One sensor loses the line: the matching wheel stops while the other keeps running.
- Neither sensor active: both wheels stop.

The PWM frequency is approximately 500 Hz and the control state is refreshed every 10 ms. The compare value and sensor polarity are demonstration settings.

## Usage

Connect the tracking sensors and both motor-driver PWM inputs. Open the Keil project under `Projects/MDK-ARM`, build, and flash it. Tune PWM values, sensor spacing, mounting height, and sensitivity to match the track and vehicle.

## License

This project is licensed under the **MIT License**. Copyright (c) 2026 JesMicro. See the [LICENSE](LICENSE) file in this project's root for the full terms. Third-party components are subject to their respective licenses.
