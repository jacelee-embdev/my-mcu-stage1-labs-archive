[简体中文](README_zh.md) | **English**

# STM32F103ZET6 Smart Home NB Integration

## Overview

This project is a more integrated version of the ZET6 smart-home exercise. It includes matrix-keypad password entry, an OLED interface, W25Q128 password storage, automatic lighting, gas alarms, fan and door control, Bluetooth/voice commands, DHT11 sensing, and ESP8266 MQTT connectivity.

## Features

- Initializes the peripherals and connects to the MQTT platform at startup.
- Accepts keypad passwords and supports confirmation and old-password verification for changes.
- Uses scheduled tasks for ambient-light control, gas alarms, and environmental uploads.
- Accepts Bluetooth or voice commands for the lamp, fan, and door.

`NB` distinguishes this archived variant; the actual network implementation in the source uses an ESP8266 and MQTT.

## Usage

Because many peripherals are involved, test power, UARTs, sensors, actuators, and networking in stages. Open the Keil project under `Projects/MDK-ARM`, build, and flash it. Before testing network features, enter the user's own Wi-Fi, MQTT, and OneNET device settings.
