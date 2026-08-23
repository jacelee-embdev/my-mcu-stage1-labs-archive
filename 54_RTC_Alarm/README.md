**English** | [简体中文](README_zh.md)

# STM32F103C8T6 RTC Alarm

## Overview

This project adds an Alarm A interrupt to the RTC time example. On first initialization, it sets the date, time, and alarm. When the target time is reached, execution enters `RTC_Alarm_IRQHandler()` and the HAL callback prints an alarm message through USART1.

## Features

- Runs the RTC from LSE and uses a BKP marker to avoid repeated setup.
- Initially sets the time to 2026-01-24 21:40:00.
- Sets Alarm A to 21:40:20 and enables the RTC alarm interrupt.
- Continues reading the clock and alternating two LEDs.

## Runtime Notes

The current alarm action is serial output only; it does not operate a buzzer. If the initialization marker already exists, the test time and alarm are not rewritten.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK. Clear the backup domain when repeating the first-run test, then build, flash, and monitor USART1.

## Key Files

- `Drivers/BSP/rtc/rtc.c`: Alarm setup, ISR, and callback.
- `Users/main.c`: Initial time and alarm configuration.

