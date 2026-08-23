[简体中文](README_zh.md) | **English**

# STM32 PWM Car Speed Control

## Overview

This experiment uses two TIM2 PWM channels to control the enable inputs of the left and right motor channels independently. Direction GPIO selects rotation direction, while PWM duty cycle controls the effective drive level. The project demonstrates basic speed adjustment and differential steering.

## Behavior

TIM2 produces an approximately 50 kHz PWM signal. The program repeats three left/right compare-value pairs: left slow and right fast, left fast and right slow, then both wheels at the same value. Each pair remains active for about one second so the steering effect is easy to observe.

## Hardware and Usage

TIM2_CH1 on PA0 drives the left PWM input, and TIM2_CH2 on PA1 drives the right. Connect these signals to a motor driver, never directly to a motor. Open the Keil project under `Projects/MDK-ARM`, build, and flash it. Recalibrate the PWM frequency and compare values for the driver, motor, supply, and vehicle load.
