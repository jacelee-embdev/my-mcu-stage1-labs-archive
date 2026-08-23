**English** | [简体中文](README_zh.md)

# STM32F103C8T6 CAN Transmit/Receive

## Overview

This project verifies CAN transmission and reception with CAN1 internal loopback mode, so a second CAN node is not required. Pressing Button 1 increments an eight-byte payload and sends an extended frame. The looped-back frame enters FIFO0 and is printed through USART1.

## Features

- Configures CAN1 for `CAN_MODE_LOOPBACK`.
- Uses a 32-bit mask filter that accepts all identifiers.
- Sends an eight-byte data frame with extended ID `0x12345678`.
- Prints every transmitted and received byte.
- Uses PA0 as the send button and two LEDs as foreground indicators.

## Runtime Notes

Loopback traffic does not use an external transceiver or bus. Before switching to normal mode, verify GPIO clocks, bit timing, CAN pins, transceiver wiring, and termination.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, build and flash it, then press the button and view the UART log.

## Key Files

- `Drivers/BSP/can/can.c`: CAN setup, filtering, transmit, and receive.
- `Users/main.c`: Test frame and button logic.

