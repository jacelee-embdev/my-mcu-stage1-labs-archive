[简体中文](README_zh.md) | **English**

# STM32 Quadrature Encoder Test

## Overview

This experiment uses an STM32 timer in hardware encoder mode to read A/B quadrature signals. TI12 mode counts transitions from both channels, determines direction from their phase relationship, and applies input filtering to reduce glitches.

## Behavior

Once per second, the main loop calls `encoder_get_count_delta()`. The function returns the signed count accumulated since the previous call and resets the timer counter to zero. The delta is printed as `COUNT` through the 115200-baud debug UART, and the LED toggles at the same interval.

The sign indicates direction and the magnitude indicates pulse change during the sample period. It is not yet a distance or rotational speed. Conversion requires encoder line count, quadrature multiplication, gearbox ratio, and sample time.

## Usage

Connect the encoder A/B channels to the configured timer inputs with compatible voltage levels and a shared ground. Open the Keil project under `Projects/MDK-ARM`, build, and flash it. Rotate the encoder slowly in both directions and verify that the sign reverses.
