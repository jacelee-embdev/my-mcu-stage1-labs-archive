[简体中文](README_zh.md) | **English**

# MPU6050 Raw Data Readout

## Overview

This experiment uses software I2C to read a 14-byte MPU6050 data frame beginning at the accelerometer X-axis high-byte register. It combines each high/low byte pair into signed 16-bit values for three-axis acceleration, raw temperature, and three-axis angular velocity.

## Behavior

The sensor is configured for a 100 Hz sample rate, a 5 Hz digital low-pass filter, a ±2000 dps gyroscope range, and a ±16 g accelerometer range. About once per second, the main loop reads and prints all seven raw values through the 115200-baud debug UART and toggles the LED.

The output contains raw register counts. It is not yet converted into degrees per second, g, degrees Celsius, or other physical units, and no offset calibration is applied.

## Usage

Open the Keil project under `Projects/MDK-ARM`, build, and flash it. Keep the module still to observe noise and zero offsets. Add scale conversion, bias compensation, and filtering when physical measurements are required.
