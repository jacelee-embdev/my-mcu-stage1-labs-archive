**English** | [简体中文](README_zh.md)

# STM32F103C8T6 Variable-Length UART RX

## Overview

This project receives variable-length data through USART1 RXNE interrupts. Each byte is stored in a buffer. The main loop compares the receive count across consecutive checks; when the count stops changing, the current bytes are treated as one complete frame and echoed.

## Features

- Stores interrupt-received bytes in a 128-byte buffer.
- Detects the end of a frame when the byte count no longer changes.
- Prints completed data with the `recv:` prefix through `printf()`.
- Clears the buffer after processing and waits for the next frame.

## Runtime Notes

USART1 uses PA9/PA10 at 115200-8-N-1. Frame boundaries depend on foreground polling and gaps between transmitted bytes. This is a learning example of software timeout framing, not a strict communication protocol.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, build and flash it, then send strings of different lengths.

## Key Files

- `Drivers/SYSTEM/uart1/uart1.c`: Interrupt buffering and software framing.
- `Users/main.c`: Continuous receive processing.

