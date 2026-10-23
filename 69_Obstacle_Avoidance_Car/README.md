**English** | [简体中文](README_zh.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32 Ultrasonic Obstacle-Avoidance Car

## Overview

This experiment combines an HC-SR04 ultrasonic sensor, a servo, and two DC motors. It demonstrates how a car can scan the available space to its left and right, compare the measured distances, and select the clearer turning direction.

## Current Behavior

The loop reads the front distance and stops the motors. The servo then points left, center, and right while the ultrasonic module takes measurements. The car turns toward the side with the larger distance for about 200 ms, stops, and returns the servo to center. Distances are printed through the debug UART.

The current program does not include continuous forward motion. It is therefore a scan-and-turn obstacle-avoidance step demo, not a complete autonomous cruising controller.

## Usage

Open the Keil project under `Projects/MDK-ARM`, build, and flash it. Calibrate servo angles and ranging first, then test the motor directions with raised wheels. Add forward-motion and safety-distance conditions for continuous avoidance.

## License

This project is licensed under the **MIT License**. Copyright (c) 2026 JesMicro. See the [LICENSE](LICENSE) file in this project's root for the full terms. Third-party components are subject to their respective licenses.
