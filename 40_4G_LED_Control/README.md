**English** | [简体中文](README_zh.md)

# STM32F103C8T6 4G LED Control

## Overview

This project receives transparent data from an E840 4G module through USART2 and controls LED1 from text commands. A message containing `ON` turns the LED on, while `OFF` turns it off. USART1 also reports received content for debugging.

## Features

- Initializes the E840 UART at 115200 baud.
- Stores received bytes through the RXNE interrupt.
- Uses software idle detection to decide when a message is complete.
- Parses `ON` and `OFF` to control LED1 on PB8.

## Runtime Notes

This project implements only the serial link between the STM32 and an already configured 4G module. It does not configure SIM registration, mobile networking, or remote server parameters.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK. Configure the E840 transparent link first, connect it to USART2, then build and flash the project.

## Key Files

- `Drivers/BSP/4G_e840/`: UART transmission and buffering.
- `Users/main.c`: Command parsing and LED control.

