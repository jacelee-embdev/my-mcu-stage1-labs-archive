**English** | [简体中文](README_zh.md)

# STM32F103C8T6 LCD1602 String Display

## Overview

This project extends the LCD1602 character driver with a string-output function. The display uses an 8-bit parallel bus. After initialization, the program writes test strings from selected columns on both rows, verifying consecutive character output and row/column positioning.

## Features

- Implements LCD1602 startup, command, and data-write timing.
- Provides functions for displaying one character or a complete string by row and column.
- Displays `LiZhiQiu` on the first row and `Handsom` on the second row.

## Hardware

| LCD1602 Signal | STM32 Pin |
|---|---|
| D0–D7 | PA0–PA7 |
| RS / RW / EN | PB1 / PB2 / PB10 |

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, connect the LCD1602, then build and flash the project. To change the text, edit the row, column, and string arguments in `main.c`.

## Key Files

- `Drivers/BSP/lcd1602/`: LCD1602 parallel driver.
- `Users/main.c`: Two-line string example.

