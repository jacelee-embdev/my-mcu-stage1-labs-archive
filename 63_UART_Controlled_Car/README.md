[简体中文](README_zh.md) | **English**

# STM32 UART-Controlled Car

## Overview

This experiment receives text commands from a PC or another serial device through USART2. A receive-idle interrupt identifies a complete message and immediately controls the two-wheel car. The main loop remains empty because reception and action dispatch occur in the interrupt path.

## Commands

- `M1`: forward.
- `M2`: backward.
- `M3`: turn left.
- `M4`: turn right.
- Any other message: stop.

USART2 runs at 115200 baud. The driver folder retains the name `bluetooth`, but this project can be tested directly with a USB-to-UART adapter.

## Usage

Connect the serial adapter and motor driver, ensure compatible voltage levels, and share ground. Open the Keil project under `Projects/MDK-ARM`, build, and flash it, then send complete commands from a serial terminal. Raise the wheels for the first test and verify every direction before driving on the floor.
