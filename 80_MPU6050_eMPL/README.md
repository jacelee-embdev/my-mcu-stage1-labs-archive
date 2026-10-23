**English** | [简体中文](README_zh.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# MPU6050 eMPL/DMP Attitude Calculation

## Overview

This experiment ports MPU6050 eMPL/DMP support to the STM32F103C8T6. The sensor's Digital Motion Processor handles motion data, while the main loop polls the FIFO and retrieves pitch, roll, and yaw angles.

## Behavior

Initialization wakes the MPU6050 and loads the DMP firmware. The main loop attempts to retrieve a sample every 5 ms so the FIFO is drained promptly. After approximately 100 successful samples, it prints `pitch`, `roll`, and `yaw` through the debug UART and toggles the LED as a heartbeat.

Yaw is derived without an absolute magnetic heading reference and can drift over time. Sensor mounting direction, vibration, and static gyro bias also affect the result.

## Usage

Connect the MPU6050 reliably, open the Keil project under `Projects/MDK-ARM`, build, and flash it, then monitor the 115200-baud UART. Keep the module still during startup and avoid long blocking work in the loop, which could allow the FIFO to overflow.

## License

This project is licensed under the **MIT License**. Copyright (c) 2026 JesMicro. See the [LICENSE](LICENSE) file in this project's root for the full terms. Third-party components are subject to their respective licenses.
