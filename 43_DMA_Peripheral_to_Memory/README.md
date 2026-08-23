**English** | [简体中文](README_zh.md)

# STM32F103C8T6 DMA Peripheral-to-Memory

## Overview

This project uses DMA1 channel 5 to move USART1 receive data into a memory buffer. Initialization calls `HAL_UART_Receive_DMA()`. DMA reads bytes from the fixed UART data register and writes them sequentially into a 128-byte buffer.

## Features

- Links DMA1_Channel5 to USART1_RX.
- Keeps the peripheral address fixed and increments the memory address.
- Starts one fixed-length receive operation in normal mode.
- Alternates two LEDs while DMA handles reception.

## Runtime Notes

The example focuses on receive-DMA configuration and does not implement a complete variable-length message protocol. Inspect `uart1_rx_buf` in the debugger, or add DMA-complete and UART-IDLE callbacks for application-level processing.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, connect USART1, then build, flash, and send test data.

## Key Files

- `Drivers/BSP/dma/dma.c`: USART1_RX DMA setup.
- `Drivers/SYSTEM/uart1/`: UART driver and receive buffer.

