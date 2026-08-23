**English** | [简体中文](README_zh.md)

# STM32F103C8T6 Bluetooth Relay Outlet

## Overview

This project controls a relay outlet from a serial Bluetooth module. USART2 receives variable-length commands. After the IDLE interrupt marks the end of a message, the code searches the text: `ON` energizes the relay and `OFF` releases it.

## Features

- Receives Bluetooth commands through USART2 at 115200 baud.
- Buffers bytes with RXNE and detects command completion with IDLE.
- Drives the relay on PB6 with an active-low output.
- Mirrors received Bluetooth content to USART1 for debugging.

## Hardware and Safety

The Bluetooth module uses PA2/PA3 and the relay control uses PB6. If the relay switches mains voltage, use a properly isolated and protected module and perform all wiring with power removed.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK. Start with a low-voltage test load, build and flash the project, then send `ON` or `OFF` from a Bluetooth terminal.

## Key Files

- `Drivers/BSP/bluetooth/`: Command reception and parsing.
- `Drivers/BSP/relay_plugin/`: Relay driver.

