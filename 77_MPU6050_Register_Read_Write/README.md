**English** | [简体中文](README_zh.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# MPU6050 Single-Register Read and Write

## Overview

This experiment uses STM32F103C8T6 GPIO to implement software I2C and exercise basic MPU6050 register access. The driver manually generates start and stop conditions, sends and receives bytes, and handles ACK/NACK responses without using the MCU hardware I2C peripheral.

## Tests

- Sends the device address and prints the MPU6050 acknowledgment state.
- Reads the `WHO_AM_I` register; a normal device usually returns `0x68`.
- Writes the power-management register to wake the sensor.
- Writes a test value to the sample-rate divider and reads it back through the debug UART.

After the one-time communication test, the LED toggles once per second as a heartbeat.

## Usage

Connect SCL, SDA, power, and ground, and ensure suitable bus pull-ups. Open the Keil project under `Projects/MDK-ARM`, build, and flash it. View output at 115200 baud. If no acknowledgment is received, check wiring, pull-ups, logic voltage, and the device address first.

## License

This project is licensed under the **MIT License**. Copyright (c) 2026 JesMicro. See the [LICENSE](LICENSE) file in this project's root for the full terms. Third-party components are subject to their respective licenses.
