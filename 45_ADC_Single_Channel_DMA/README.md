**English** | [简体中文](README_zh.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# STM32F103C8T6 Single-Channel ADC with DMA

## Overview

This project continuously samples PA1 with ADC1 and uses DMA1 channel 1 to update a 16-bit memory value automatically. Circular DMA lets the main loop read the latest conversion and report its voltage without waiting for each ADC operation.

## Features

- Runs ADC1 channel 1 continuously with 12-bit right-aligned data.
- Calibrates the ADC and uses a 239.5-cycle sample time.
- Transfers halfwords from peripheral to memory in circular DMA mode.
- Periodically reports the latest voltage through USART1.

## Hardware Notes

Connect the analog input to PA1 and keep it between 0 and 3.3 V. DMA continuously overwrites `adc_result` with the newest sample.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, connect the analog source, then build and flash the project.

## Key Files

- `Drivers/BSP/adc/adc.c`: ADC and circular DMA configuration.
- `Users/main.c`: Result reading and voltage output.

## License

This project is licensed under the **MIT License**. Copyright (c) 2026 JesMicro. See the [LICENSE](LICENSE) file in this project's root for the full terms. Third-party components are subject to their respective licenses.
