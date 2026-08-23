**English** | [简体中文](README_zh.md)

# STM32F103C8T6 DMA Memory-to-Memory

## Overview

This project demonstrates a memory-to-memory transfer with DMA1 channel 1. The source buffer contains sixteen patterned 32-bit values. DMA copies the complete byte range to a destination buffer, and USART1 prints the destination values for verification.

## Features

- Configures DMA1_Channel1 for `MEMORY_TO_MEMORY`.
- Enables address increment for both source and destination.
- Transfers 64 bytes once in normal mode.
- Polls the transfer-complete flag and prints sixteen destination words.

## Behavior

The serial terminal first shows the destination buffer, which should match the source array. Two LEDs then alternate continuously as a running indicator.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, build and flash it, then inspect the copied values in a 115200-baud terminal.

## Key Files

- `Drivers/BSP/dma/dma.c`: DMA configuration, test arrays, and output.
- `Users/main.c`: Transfer start.

