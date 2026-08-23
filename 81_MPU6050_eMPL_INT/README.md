[简体中文](README_zh.md) | **English**

# MPU6050 eMPL/DMP Interrupt Readout

## Overview

This experiment adds the MPU6050 data-ready interrupt to the eMPL/DMP attitude project. The sensor INT signal is connected to an STM32F103C8T6 rising-edge EXTI input, so DMP data is read in response to a hardware event instead of continuous polling.

## Behavior

The external-interrupt callback reads pitch, roll, and yaw and uses a software divider to reduce the UART print rate. The main loop only toggles the LED every 500 ms and prints a heartbeat message. This makes the project useful for validating the MPU6050 INT connection, EXTI configuration, and DMP timing.

The current learning implementation performs DMP reads and serial output inside the interrupt callback. A more robust design should only set a flag in the ISR and perform time-consuming work in the main loop.

## Usage

Connect the sensor INT line in addition to I2C. Open the Keil project under `Projects/MDK-ARM`, build, and flash it, then observe attitude and heartbeat output at 115200 baud.
