[简体中文](README_zh.md) | **English**

# STM32 Three-Day Weather Forecast

## Overview

This experiment uses an STM32F103C8T6 and ESP8266 to request weather data. cJSON parses the date, weather code, high temperature, and low temperature for the next three days. The results are shown on an OLED, with weather codes converted to matching Chinese weather icons.

## Features

- Retrieves and stores a three-day forecast.
- Button 1 cycles through the three forecast pages.
- Button 2 refreshes the data and returns to the current day.
- Serial output helps diagnose network and JSON parsing problems.

## Usage

Connect the ESP8266, OLED, and buttons, then enter your own Wi-Fi, weather API key, and query location. Open the `.uvprojx` file under `Projects/MDK-ARM` with Keil MDK, build, and flash it.

## Main Code

- `Users/main.c`: refresh and page-selection logic.
- `Drivers/BSP/weather/`: requests, parsing, and weather display.
- `Drivers/BSP/esp8266/` and `Drivers/BSP/oled/`: communication and display drivers.
