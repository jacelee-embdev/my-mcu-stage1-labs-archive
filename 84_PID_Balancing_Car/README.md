**English** | [简体中文](README_zh.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32 PID Two-Wheel Balancing Car

## Overview

This project combines MPU6050 DMP attitude data, two wheel encoders, dual motor PWM, and Bluetooth commands for a two-wheel self-balancing car. An MPU6050 data-ready interrupt sets a flag. The main loop then reads attitude, gyroscope, and encoder data, evaluates the control loops, and drives both motors.

## Control Structure

- Balance loop: PD control using pitch and Y-axis angular rate.
- Velocity loop: PI control using both encoder deltas, with integral limiting.
- Turn loop: PD control using the Bluetooth target and Z-axis angular rate.
- The mixed left/right outputs are clamped to ±7000.

Bluetooth commands select standby, adjust target speed, and request left or right turns. The stored gains and mechanical zero are only starting values and will not suit every chassis.

## Safety

Secure or raise the chassis while verifying attitude sign, encoder sign, and motor direction. A reversed signal can command immediate full power. Tune from small values and keep a motor-power cutoff ready. Open the Keil project under `Projects/MDK-ARM`, build, and flash it only after these checks.

## License

This project is licensed under the **MIT License**. Copyright (c) 2026 JesMicro. See the [LICENSE](LICENSE) file in this project's root for the full terms. Third-party components are subject to their respective licenses.
