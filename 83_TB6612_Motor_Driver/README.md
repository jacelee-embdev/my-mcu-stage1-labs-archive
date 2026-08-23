[简体中文](README_zh.md) | **English**

# STM32 TB6612 Dual-Motor Driver

## Overview

This experiment provides a two-channel DC motor driver suitable for a TB6612-style dual H-bridge module. PB12–PB15 select the left and right motor directions. TIM1_CH1 on PA8 and TIM1_CH4 on PA11 generate PWM. `motor_set_speed()` uses each parameter's sign for direction, magnitude for duty, and zero for stop.

## Current State

The driver includes a complete test sequence for independent forward/reverse motion, multiple speeds, synchronized movement, pivot turns, and differential turns. However, `motor_test_sequence()` is commented out in the active `main.c`, so the downloaded program initializes the driver but does not intentionally run the motors.

## Usage

Verify TB6612 supply, standby/enable, direction, and PWM wiring before enabling the test call. Open the Keil project under `Projects/MDK-ARM`, build, and flash it. Raise the wheels, limit supply current, and keep an immediate power cutoff available. PWM compare values use ARR = 7199.
