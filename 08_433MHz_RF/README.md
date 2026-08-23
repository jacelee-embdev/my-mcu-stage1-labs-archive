**English** | [简体中文](README_zh.md)

# STM32F103C8T6 433 MHz RF Receiver

## Overview

This project reads two digital outputs from a 433 MHz RF receiver to identify the A and B buttons of a remote control. PA5 and PA12 are configured as rising-edge external-interrupt inputs. Each interrupt sets an event flag, which is then handled in the main loop to toggle an LED.

## Features

- Configures PA5 and PA12 as two EXTI inputs.
- Stores separate event flags for remote buttons A and B.
- Button A toggles LED1, while Button B toggles LED2.

## Hardware and Behavior

| Module | Pin |
|---|---|
| 433 MHz A / B outputs | PA5 / PA12 |
| LED1 / LED2 | PB8 / PB9 |

When the receiver recognizes a remote button, the matching LED changes state once.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK. Connect the paired receiver outputs to the specified pins, then build and flash the project.

## Key Files

- `Users/main.c`: RF button event handling.
- `Drivers/BSP/EXTI/`: Receiver interrupts and flags.

