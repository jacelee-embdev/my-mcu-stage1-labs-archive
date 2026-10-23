**English** | [简体中文](README_zh.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32 Basic Car Movement

## Overview

This experiment verifies basic direction control for a two-wheel DC motor car. The STM32F103C8T6 controls the direction inputs of the left and right motor channels, making the car move forward, backward, turn left, turn right, and stop.

## Behavior

The five actions run repeatedly, with each action held for about one second. The project demonstrates how left- and right-wheel direction combinations determine the motion of the complete car. It also provides the motor foundation used by later UART, tracking, following, and obstacle-avoidance experiments.

## Hardware and Usage

PB0/PB1 control the left motor direction and PB2/PB10 control the right. Use a proper motor driver board; never connect a motor directly to MCU GPIO. Supply the motors appropriately and share ground with the controller. Open the Keil project under `Projects/MDK-ARM`, verify the wiring, build, and flash it. If a wheel rotates backward, swap its motor leads or adjust the direction logic.

## License

This project is licensed under the **MIT License**. Copyright (c) 2026 JesMicro. See the [LICENSE](LICENSE) file in this project's root for the full terms. Third-party components are subject to their respective licenses.
