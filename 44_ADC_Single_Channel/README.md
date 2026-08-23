**English** | [简体中文](README_zh.md)

# STM32F103C8T6 Single-Channel ADC

## Overview

This project samples one analog voltage with ADC1 in polling mode. PA1 is configured as ADC channel 1. Each reading starts a 12-bit conversion in software, waits for completion, and converts the raw result to volts using a 3.3 V reference.

## Features

- Uses ADC1 in single-channel, non-continuous, software-triggered mode.
- Performs ADC calibration at startup and uses a 239.5-cycle sample time.
- Reads the 0–4095 value from PA1/ADC1_IN1.
- Periodically prints the converted voltage through USART1.

## Hardware Notes

Connect a 0–3.3 V potentiometer or analog source to PA1. Keep the input within the MCU's allowed range and connect all grounds together.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, connect the analog source, then build and flash the project.

## Key Files

- `Drivers/BSP/adc/adc.c`: ADC setup, channel configuration, and polling.
- `Users/main.c`: Voltage conversion and output.

