**English** | [简体中文](README_zh.md)

# STM32F103C8T6 Queue-Control System

## Overview

This project implements a simple batch access-control system. An infrared sensor counts passing people, while an LCD1602 shows the current state and count. After five people pass, the gate closes for five seconds and then reopens automatically. If the sensor is triggered during the waiting state, the buzzer plays an alarm pattern.

## Features

- Opens the gate and counts people in the `PASS` state.
- Enters `WAIT` and closes the gate after five people.
- Displays `PASS`, `WAIT`, and count progress on the LCD1602.
- Uses two LEDs as state indicators and a buzzer for invalid passage.
- Organizes behavior with SysTick counters and foreground task polling.

## Hardware

The infrared sensor uses PB4, the gate relay PB6, and the buzzer PB5. The LCD1602 uses a parallel interface.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, connect the modules, then build and flash the project. The batch size and waiting time can be changed in `tasks.c`.

## Key Files

- `Drivers/BSP/tasks/tasks.c`: State, counting, and task logic.
- `Drivers/BSP/exti/`, `lcd1602/`, `relay_gate/`, and `beep/`: Peripheral drivers.

