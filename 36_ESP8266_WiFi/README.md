**English** | [简体中文](README_zh.md)

# STM32F103C8T6 ESP8266 Wi-Fi Connection

## Overview

This project extends the ESP8266 UART driver with a Wi-Fi join sequence. Initialization checks AT communication, selects Station mode, enables single-connection mode, and joins the configured wireless network with its SSID and password.

## Features

- Receives ESP8266 AT responses through USART2 interrupts.
- Retries the AT test, operating-mode setup, and connection-mode setup.
- Uses `AT+CWJAP` to join a configured access point.
- Treats `WIFI GOT IP` as the successful connection response.
- Alternates two LEDs in the main loop as a running indicator.

## Configuration

Set your Wi-Fi SSID and password in the ESP8266 configuration before use. Do not commit real credentials to a public repository; a separate ignored local configuration file is preferable.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, connect the ESP8266, then build and flash the project. View the join sequence through USART1.

## Key Files

- `Drivers/BSP/esp8266/`: AT commands, Wi-Fi join, and buffering.
- `Users/main.c`: Initialization and running indicator.

