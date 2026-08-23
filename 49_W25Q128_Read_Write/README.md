**English** | [简体中文](README_zh.md)

# STM32F103C8T6 W25Q128 Read/Write

## Overview

This project drives a W25Q128 NOR Flash through SPI1 and demonstrates device-ID reading, sector erase, page programming, and data reading. It erases the sector containing address `0x000000`, writes four test bytes, reads them back, and prints the result through USART1.

## Features

- Communicates with W25Q128 through SPI1 and a dedicated chip-select pin.
- Reads the manufacturer/device ID.
- Supports 4 KB sector erase, up to 256-byte page writes, and sequential reads.
- Writes and verifies `AA BB CC DD`.

## Hardware and Data Safety

SPI1 normally uses PA5/PA6/PA7, with chip select on PA4. Startup erases Flash sector 0, permanently removing any existing data in that sector. Confirm the test area is disposable before running it.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, connect the 3.3 V Flash device, then build and flash the project.

## Key Files

- `Drivers/BSP/w25q128/`: SPI Flash commands and operations.
- `Users/main.c`: Erase/write/read verification.

