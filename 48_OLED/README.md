**English** | [简体中文](README_zh.md)

# STM32F103C8T6 OLED Display Experiment

## Overview

This project implements a software-I²C driver for a 128×64 OLED and demonstrates Latin characters, numbers, punctuation, Chinese glyphs, and bitmap images. After the tests, it plays a startup animation and enters a simulated desktop showing time, CPU load, a progress bar, and temperature.

## Features

- Bit-bangs I²C SCL/SDA on PB6/PB7.
- Supports clear, cursor positioning, characters, strings, Chinese glyphs, and images.
- Includes inversion, logo, and boot-progress animation effects.
- Periodically refreshes a desktop layout with sample status data.

## Runtime Notes

The desktop time, load, and temperature are demonstration variables rather than real sensor or system measurements. Fonts and bitmap data are stored with the display driver resources.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, connect a compatible OLED, then build and flash the project.

## Key Files

- `Drivers/BSP/oled/`: OLED and software-I²C driver.
- `Drivers/BSP/boot_animation/`: Animation and desktop UI.

