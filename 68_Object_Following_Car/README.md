[简体中文](README_zh.md) | **English**

# STM32 Infrared Object-Following Car

## Overview

This experiment uses left and right infrared detection modules for simple object following. The STM32F103C8T6 reads sensor inputs on PB5 and PB6, then controls the two motors according to the detected target direction.

## Control Logic

- Both sensors detect the target: move forward.
- Only the right sensor detects it: turn right.
- Only the left sensor detects it: turn left.
- Neither sensor detects it: stop.

The driver treats a low level as active and prints both sensor states through the debug UART. This approach does not measure actual distance and works best as a short-range demonstration under stable reflective and lighting conditions.

## Usage

Mount the sensors symmetrically and adjust their sensitivity. Open the Keil project under `Projects/MDK-ARM`, build, and flash it. If the car turns away from the target, check the left/right sensor labels, output polarity, and motor directions.
