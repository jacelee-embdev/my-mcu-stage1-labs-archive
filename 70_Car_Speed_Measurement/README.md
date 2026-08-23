[简体中文](README_zh.md) | **English**

# STM32 Car Speed Measurement

## Overview

This experiment counts falling-edge pulses from a wheel-speed sensor on PB12. TIM2 creates a 100 ms measurement window, after which the pulse count is printed through the debug UART and reset. The program starts the car moving forward after initialization.

## Measurement Principle

Every valid sensor pulse increments a counter. The timer callback reports and clears that counter at a fixed interval. Although the output label is `speed`, the current value is actually pulses per 100 ms, not a calibrated result in cm/s or m/s.

## Usage

Connect the speed sensor and motor driver, open the Keil project under `Projects/MDK-ARM`, build, and flash it. View the output at 115200 baud. To calculate physical speed, include the number of pulses per wheel revolution, wheel circumference, gearbox ratio, and exact sample period. Test with raised wheels first and confirm reliable pulse detection before driving.
