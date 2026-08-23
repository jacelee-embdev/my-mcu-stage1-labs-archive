[简体中文](README_zh.md) | **English**

# STM32 Car Speed Display and Bluetooth Report

## Overview

This experiment extends wheel-pulse measurement with a local OLED display and Bluetooth serial reporting. A falling-edge interrupt on PB12 accumulates speed-sensor pulses. Every 100 ms, TIM2 reads and clears the count, displays the result, and sends the same text through USART2.

## Behavior

The car moves forward after startup. The displayed and transmitted format is `speed:xx cm/s`. The current code uses the raw pulse count from each 100 ms window directly, so the stated unit is only a demonstration and has not been calibrated against wheel geometry.

## Usage

Connect the sensor, OLED, Bluetooth module, and motor driver. Open the Keil project under `Projects/MDK-ARM`, build, and flash it. USART2 runs at 115200 baud. For accurate measurements, add a conversion based on pulses per revolution, wheel circumference, gearbox ratio, and the sampling interval.
