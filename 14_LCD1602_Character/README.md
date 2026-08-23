**English** | [简体中文](README_zh.md)

# STM32F103C8T6 LCD1602 Character Display

## Overview

This project implements an 8-bit parallel LCD1602 driver and displays one character at a selected position. PA0–PA7 form the data bus, while PB1, PB2, and PB10 carry the RS, RW, and EN control signals. After initialization, the program writes the character `L` to the display.

## Features

- Follows the LCD1602 startup sequence and configures its display mode.
- Provides separate command and character-data write functions.
- Selects a character position through the display address.
- Alternates two LEDs in the main loop as a running indicator.

## Hardware

| LCD1602 Signal | STM32 Pin |
|---|---|
| D0–D7 | PA0–PA7 |
| RS / RW / EN | PB1 / PB2 / PB10 |

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, wire the display as shown, then build and flash the project. Connect the LCD contrast pin through a suitable potentiometer.

## Key Files

- `Drivers/BSP/lcd1602/`: Parallel LCD driver.
- `Users/main.c`: Single-character example.

