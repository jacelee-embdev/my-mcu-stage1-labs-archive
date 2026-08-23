[简体中文](README_zh.md) | **English**

# STM32 Voice-Controlled Car Framework

## Overview

This experiment reads three digital outputs from a voice-recognition module and provides a framework for selecting line-tracking, infrared-following, and ultrasonic obstacle-avoidance modes. The voice inputs are connected to PA2, PA1, and PA0 and form several three-bit command codes.

## Current Status

The main loop currently samples the voice pins once per second and prints codes such as `001`, `010`, `011`, `100`, `101`, and `110`. The project already contains helper functions for line tracking, object following, and servo-based ultrasonic scanning. However, those functions are not yet mapped to voice codes in the active main loop.

This version is therefore a voice-code test and multi-mode integration scaffold, not a finished voice-driving program.

## Usage

Open the Keil project under `Projects/MDK-ARM`, build, and flash it. Verify stable voice codes first, then add the desired code-to-action mapping in `Users/main.c`. Add a default stop state and link-loss protection before powered motor tests.
