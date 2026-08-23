[简体中文](README_zh.md) | **English**

# STM32 4G Remote-Controlled Car

## Overview

This experiment connects a preconfigured 4G transparent-transmission module to USART2. Control commands and speed reports can then pass through a cellular connection. The STM32F103C8T6 parses movement messages in the UART idle-line interrupt and sends a periodic speed string back to the remote endpoint.

## Features

- `M1`: forward, `M2`: backward, `M3`: left, and `M4`: right; other input stops the car.
- A PB12 external interrupt counts wheel-sensor pulses.
- TIM2 updates the OLED and USART2 report every 100 ms.

The serial driver directory is still named `bluetooth`, but this project uses it as a generic USART2 transport. SIM registration and server connection are expected to be configured on the 4G module.

## Usage

Verify module power, logic levels, baud rate, and network connection before flashing the Keil project. Calibrate the displayed speed for the actual wheel system, and test motor directions with raised wheels.
