[简体中文](README_zh.md) | **English**

# STM32 Wi-Fi Car Control and Speed Report

## Overview

This experiment uses an ESP8266 transparent network connection for remote car control and speed reporting. The STM32F103C8T6 parses server text commands to control the motors, counts wheel-sensor pulses on PB12, and sends the result to both the OLED and the remote endpoint.

## Control and Reporting

- `M1`, `M2`, `M3`, and `M4` select forward, backward, left, and right; other input stops the car.
- TIM2 processes the pulse count every 100 ms.
- A speed string is displayed locally and transmitted through the ESP8266.

The reported `cm/s` value still requires calibration using wheel and encoder parameters.

## Usage

Enter the Wi-Fi, server address, and port for the target network, then open the Keil project under `Projects/MDK-ARM`, build, and flash it.
