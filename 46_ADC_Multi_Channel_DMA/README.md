**English** | [简体中文](README_zh.md)

# STM32F103C8T6 Multi-Channel ADC with DMA

## Overview

This project continuously scans four ADC1 inputs and transfers their results through circular DMA. PA0–PA3 map to ADC channels 0–3. The four conversions are stored in a fixed-order array and converted to voltages for USART1 output.

## Features

- Enables ADC1 scan and continuous-conversion modes.
- Samples ADC channels 0, 1, 2, and 3 in order.
- Uses DMA1_Channel1 to write four halfwords repeatedly.
- Reports all four 0–3.3 V conversion results.

## Hardware Notes

The analog inputs are PA0, PA1, PA2, and PA3. Keep every signal within the ADC voltage range and share a common ground.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, connect the analog inputs, then build and flash the project. View all channels in the serial terminal.

## Key Files

- `Drivers/BSP/adc/adc.c`: Scan sequence and DMA setup.
- `Users/main.c`: Four-channel result output.

