**English** | [简体中文](README_zh.md)

# STM32F103C8T6 Queue-Control Framework

## Overview

This project is the initial framework for a queue-control system. It integrates drivers for LEDs, a buzzer, a gate relay, an infrared sensor, and an LCD1602. The main loop runs two LED tasks triggered by SysTick flags, validating the layered structure and cooperative task mechanism before the full queue logic is added.

## Main Components

- Initializes the input, display, indicator, and gate-control modules.
- Shows two test strings on the LCD1602 after startup.
- Maintains 1000 ms and 500 ms software periods with SysTick.
- Uses `task1()` and `task2()` to toggle two LEDs.

## Runtime Notes

This version mainly verifies the project framework; the queue behavior has not yet been assembled into a complete state machine. The sensor, buzzer, and gate drivers are available for later passenger counting, access control, and alarm logic.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK. Wire the modules according to `Drivers/BSP/`, then build and flash the project.

## Key Files

- `Drivers/BSP/tasks/`: SysTick task framework.
- `Drivers/BSP/`: LCD, infrared, buzzer, gate, and LED drivers.

