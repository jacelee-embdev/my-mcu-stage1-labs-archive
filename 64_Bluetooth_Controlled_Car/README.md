[简体中文](README_zh.md) | **English**

# STM32 Bluetooth-Controlled Car

## Overview

This experiment adds a Bluetooth serial module to the basic UART-controlled car. A phone sends text commands over the wireless serial link. The STM32F103C8T6 receives a complete USART2 frame using RX and idle-line interrupts, then updates the left and right motor directions.

## Commands

- `M1`: forward.
- `M2`: backward.
- `M3`: turn left.
- `M4`: turn right.
- Any other message: stop.

The serial rate is 115200 baud. The simple command format makes the project suitable for testing Bluetooth transparent transmission and motor direction control.

## Usage

Connect the Bluetooth module to USART2 and confirm its voltage, baud rate, and phone-terminal line-ending settings. Open the Keil project under `Projects/MDK-ARM`, build, and flash it. Raise the wheels during initial tests and keep a quick way to disconnect motor power.
