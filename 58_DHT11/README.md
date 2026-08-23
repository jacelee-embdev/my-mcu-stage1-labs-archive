**English** | [简体中文](README_zh.md)

# STM32F103C8T6 DHT11 Temperature and Humidity

## Overview

This project reads a DHT11 temperature/humidity sensor with its single-wire timing protocol. PA5 switches between output and input. After the MCU sends the start signal, it reads 40 data bits and validates the result with the checksum byte.

## Features

- Uses PA5 as the bidirectional DHT11 data pin.
- Distinguishes data bits 0 and 1 with microsecond timing.
- Reads humidity integer/fraction, temperature integer/fraction, and checksum bytes.
- Prints temperature and relative humidity through USART1 after successful validation.
- Alternates two LEDs as a running indicator.

## Runtime Notes

DHT11 updates slowly, and this program reads it roughly once per second. The data line normally requires a pull-up; follow the module's power and logic-level specifications.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, connect the DHT11, then build and flash the project and watch USART1.

## Key Files

- `Drivers/BSP/dht11/`: Start timing, bit reading, and checksum validation.
- `Users/main.c`: Periodic acquisition.

