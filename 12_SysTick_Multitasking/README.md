**English** | [简体中文](README_zh.md)

# STM32F103C8T6 SysTick Cooperative Tasks

## Overview

This project uses a 1 ms SysTick time base and task flags to simulate simple cooperative multitasking. The interrupt routine only updates counters and raises flags. The main loop repeatedly polls the task functions, allowing two LEDs to change at independent rates without blocking delays.

## Features

- Maintains two software timers from the SysTick interrupt.
- Toggles LED1 approximately every 1000 ms.
- Toggles LED2 approximately every 500 ms.
- Runs task logic in the foreground instead of doing lengthy work inside the ISR.

## Behavior

The LEDs on PB8 and PB9 blink at different rates, demonstrating non-blocking scheduling based on a system tick. This is not an RTOS and does not provide preemption, priorities, or separate task stacks.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, build and flash the project, then observe both LEDs.

## Key Files

- `Drivers/BSP/tasks/tasks.c`: Timing counters, flags, and task functions.
- `Users/main.c`: Cooperative task polling.

