**English** | [简体中文](README_zh.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# MPU6050 Burst Read and Write

## Overview

This experiment extends the software-I2C MPU6050 driver with burst access to consecutive registers. Transferring multiple bytes after one register address reduces repeated bus start/stop sequences and prepares the code for full sensor-frame reads and DMP memory transfers.

## Tests

- Configures the sensor clock, 100 Hz sample rate, low-pass filter, and measurement ranges.
- Reads `WHO_AM_I` and validates the device ID.
- Writes four consecutive bytes beginning at the sample-rate divider register.
- Reads the same four bytes back and prints them through the UART.

The LED toggles once per second after the diagnostic completes.

## Usage

Connect the MPU6050 with proper SCL/SDA pull-ups. Open the Keil project under `Projects/MDK-ARM`, build, and flash it, then view diagnostics at 115200 baud. The test intentionally overwrites several configuration registers; run the normal initialization again before using the sensor for meaningful measurements.

## License

This project is licensed under the **MIT License**. Copyright (c) 2026 JesMicro. See the [LICENSE](LICENSE) file in this project's root for the full terms. Third-party components are subject to their respective licenses.
