**English** | [简体中文](README_zh.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 DMA Memory-to-Peripheral

## Overview

This project uses DMA to send memory data through USART1. It fills a buffer with 1000 `A` characters, then DMA1 channel 4 moves those bytes into the UART data register without CPU-driven byte-by-byte polling.

## Features

- Links DMA1_Channel4 to USART1_TX.
- Increments the memory address while keeping the peripheral address fixed.
- Sends 1000 bytes once in normal mode.
- Continues alternating two LEDs after the DMA transfer starts.

## Behavior

USART1 on PA9 outputs 1000 consecutive `A` characters at 115200-8-N-1. The LED loop shows that foreground code continues to run.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, connect a serial terminal, then build and flash the project.

## Key Files

- `Drivers/BSP/dma/dma.c`: USART1_TX DMA configuration.
- `Users/main.c`: Test-buffer creation and transmission.

## License

This project is licensed under the **MIT License**. Copyright (c) 2026 JesMicro. See the [LICENSE](LICENSE) file in this project's root for the full terms. Third-party components are subject to their respective licenses.
