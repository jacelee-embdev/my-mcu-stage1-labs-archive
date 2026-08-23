**English** | [简体中文](README_zh.md)

# STM32F103C8T6 Timer-Interrupt LED

## Overview

This project demonstrates a TIM2 update interrupt. TIM2 is configured as an up-counter with update interrupts enabled. The HAL period callback toggles LED1, so the main loop does not need a blocking delay to generate the blink timing.

## Features

- Initializes TIM2, its peripheral clock, and the NVIC interrupt.
- Uses a prescaler of 7199 and an auto-reload value of 4999.
- Generates an update event approximately every 500 ms from a 72 MHz timer clock.
- Toggles the LED on PB8 in each update callback.

## Behavior

After flashing, LED1 blinks continuously with a complete on/off cycle of about one second. The experiment shows how a hardware timer can maintain timing independently of foreground code.

## Quick Start

Open `Projects/MDK-ARM/stm32f103.uvprojx` in Keil MDK, build and flash it, then observe the LED. Change the arguments to `timer_init()` to select another interrupt period.

## Key Files

- `Drivers/BSP/timer/timer.c`: TIM2 initialization, ISR, and callback.
- `Users/main.c`: Peripheral initialization entry point.

