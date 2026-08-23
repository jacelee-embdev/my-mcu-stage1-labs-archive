**English** | [简体中文](README_zh.md)

# STM32F103C8T6 Real-Time Clock

## Overview

This project combines the RTC, OLED, four buttons, and a buzzer into an adjustable clock. The OLED shows date, time, and alarm time. Buttons enter the clock or alarm setup screens, move between fields, and increase or decrease values. The selected field blinks while being edited.

## Features

- Runs the RTC from LSE and uses a BKP marker for first-time initialization.
- Displays year, month, day, time, and Alarm A on the OLED.
- Uses four buttons for set, shift, increment, and decrement operations.
- Writes edited clock and alarm values back to the RTC.
- Prints an alarm message and plays a buzzer pattern in the alarm callback.

## Runtime Notes

Default test values are written only when `0xA5A5` is absent. Buttons use PA0–PA3; see the BSP drivers for OLED and buzzer pins.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK. Connect the LSE, OLED, and buttons, then build and flash the project.

## Key Files

- `Users/main.c`: UI and setup-state flow.
- `Drivers/BSP/rtc/`, `oled/`, `key/`, and `beep/`: Clock and user-interface drivers.

