**English** | [简体中文](README_zh.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103ZET6 Smart Home Integration Lab

## Overview

This project is a smart-home integration exercise for the STM32F103ZET6. It brings together a matrix keypad, OLED, buzzer, relay lock and fan, W25Q128 flash, ADC sensors, Bluetooth, voice input, DHT11, ESP8266, and OneNET/MQTT support. The source includes components for password management, automatic lighting, gas alarms, and temperature/humidity reporting.

## Current State

The active `main.c` initializes most peripherals and performs an initial password check. Its loop currently runs `w25q128_test()` every 500 ms and prints the flash device ID. The lighting, gas, cloud-upload, and keypad password-change flows remain in the project but are commented out and require integration testing.

## Usage

Open the Keil project under `Projects/MDK-ARM` and enable one feature at a time while verifying its hardware. Do not connect every load before basic power tests. Network features require settings that match the user's own Wi-Fi network and OneNET device.

## Main Code

- `Users/main.c`: initialization and active test entry.
- `Drivers/BSP/tasks/`: lighting, alarm, and upload tasks.
- `Drivers/BSP/password/` and `w25q128/`: password and flash support.

## License

This project is licensed under the **MIT License**. Copyright (c) 2026 JesMicro. See the [LICENSE](LICENSE) file in this project's root for the full terms. Third-party components are subject to their respective licenses.
