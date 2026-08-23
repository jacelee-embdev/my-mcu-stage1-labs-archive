**English** | [简体中文](README_zh.md)

# STM32F103C8T6 Button Experiment

## Overview

This project demonstrates polled button input and GPIO output control. Two active-low buttons are connected to PA0 and PA1. The program performs simple delay-based debouncing, returns a button number, and toggles the corresponding LED on PB8 or PB9.

## Features

- Initializes two button inputs and two LED outputs.
- Uses `KeyScan()` as a common interface for reading both buttons.
- Button 1 controls LED1, while Button 2 controls LED2.

## Hardware and Behavior

| Module | Pin / Configuration |
|---|---|
| Button 1 / 2 | PA0 / PA1, active low |
| LED1 / LED2 | PB8 / PB9, active low |

Each valid button action toggles the state of its assigned LED.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, build it, and flash the board. The button modules must match the pull-up inputs and active level used by the code.

## Key Files

- `Users/main.c`: Button scanning and LED control.
- `Drivers/BSP/KEY/` and `Drivers/BSP/LED/`: Button and LED drivers.

