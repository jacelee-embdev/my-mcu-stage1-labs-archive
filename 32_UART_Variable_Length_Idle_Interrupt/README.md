**English** | [简体中文](README_zh.md)

# STM32F103C8T6 UART IDLE-Line Reception

## Overview

This project receives variable-length data with USART1 RXNE and IDLE interrupts. RXNE stores incoming bytes in a buffer. When the UART line remains idle for one frame time, the IDLE interrupt treats the buffered bytes as a complete message, prints them, and resets the buffer.

## Features

- Configures USART1 on PA9/PA10 at 115200-8-N-1.
- Uses RXNE for byte reception and buffer overflow protection.
- Uses the hardware IDLE interrupt to detect the end of a data stream.
- Prints completed data with `recv:` and clears the receive state.

## Runtime Notes

The main loop remains empty; reception and framing are handled by the USART1 interrupt. Compared with the software-count method, IDLE detection uses the UART peripheral's own line-idle capability.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, build and flash it, then send variable-length messages from a serial terminal.

## Key Files

- `Drivers/SYSTEM/uart1/uart1.c`: RXNE, IDLE handling, and buffer management.
- `Users/main.c`: Minimal entry point.

