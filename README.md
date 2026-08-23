**English** | [简体中文](README_zh.md)

# My MCU Stage 1 Labs Archive

An archive of 86 independent STM32F1 learning projects, progressing from GPIO, timers, UART, and DMA to sensors, IoT, smart cars, and PID balance control.

## About This Repository

This repository preserves the experiments and notes accumulated during the first stage of my MCU studies. Its primary purpose is to serve as a personal learning archive and cloud backup. If the local code is lost, I move to another computer, or I need to test a topic again, I can clone the relevant project and continue from the recorded state.

Projects are numbered roughly in learning order and are independent of one another. Each one can be opened, built, and flashed separately. The source preserves the implementation, debugging approach, and completion state at that point in the learning process. Some directories contain complete applications, while others intentionally test only one peripheral or communication path. Every project has a short README in English and Simplified Chinese describing what its active program does, which modules are involved, and what should be checked before running it again.

## Archive at a Glance

| Item | Description |
|---|---|
| Project count | 86 independent lab projects |
| Numbering | `00`–`84`; number `67` has two distinct versions |
| Primary MCUs | STM32F103C8T6; integrated projects `75` and `76` use STM32F103ZET6 |
| Language | C |
| Software foundation | STM32 HAL, CMSIS, and project-specific BSP drivers |
| Development environment | Keil MDK 5 with `.uvprojx` project files |
| Programming/debug | ST-Link, J-Link, or another compatible SWD probe |
| Documentation | `README.md` in English and `README_zh.md` in Simplified Chinese |

Most STM32F103 projects configure the system clock to 72 MHz. Refer to the README and source of each project for its exact pin assignments, UART settings, timers, peripherals, and active runtime behavior.

## Learning Coverage

The archive roughly follows these learning stages:

| Stage | Projects | Main Topics |
|---|---|---|
| Basic input/output | 00–09 | Project template, LEDs, buttons, external interrupts, buzzer, relay, and simple alarm applications |
| Time base and basic user interfaces | 10–19 | Delays, SysTick, task scheduling, infrared input, LCD1602, timers, and PWM |
| Timer measurement and protection | 20–29 | UART logging, input capture, pulse counting, servo, ultrasonic ranging, and watchdogs |
| Serial and wireless communication | 30–40 | Variable-length UART reception, Bluetooth, ESP8266, TCP, Wi-Fi, and 4G transparent transport |
| Data acquisition and common peripherals | 41–50 | DMA, ADC, OLED, W25Q128, matrix keypad, and integrated sensing applications |
| RTC, low power, and IoT | 51–61 | Access control, backup domain, real-time clock, low power, CAN, DHT11, OneNET, weather, and smart lamp |
| Smart cars | 62–74 | Basic motion, wireless control, PWM, tracking, following, obstacle avoidance, speed sensing, and multi-mode control |
| Integrated control | 75–84 | Smart home, MPU6050, DMP, encoders, TB6612, and a two-wheel PID balancing car |

## Complete Project Index

Select a project name to open its English documentation.

### 00–09: GPIO and Basic Applications

| No. | Project | Description |
|---:|---|---|
| 00 | [STM32F103C8T6_Template](00_STM32F103C8T6_Template/README.md) | Reusable STM32F103C8T6 HAL project template. |
| 01 | [LED](01_LED/README.md) | GPIO push-pull output and basic LED control. |
| 02 | [LED_Chaser](02_LED_Chaser/README.md) | Sequential LED switching to create a running-light effect. |
| 03 | [Buzzer](03_Buzzer/README.md) | GPIO control of a buzzer. |
| 04 | [Button](04_Button/README.md) | Button GPIO input, state detection, and basic debounce. |
| 05 | [Interrupt](05_Interrupt/README.md) | GPIO external interrupts, NVIC, and interrupt callbacks. |
| 06 | [Vibration_LED](06_Vibration_LED/README.md) | Vibration sensor input used to trigger an LED. |
| 07 | [Relay](07_Relay/README.md) | GPIO control of relay activation and release. |
| 08 | [433MHz_RF](08_433MHz_RF/README.md) | Data detection from a 433 MHz wireless receiver. |
| 09 | [Electric_Bike_Alarm](09_Electric_Bike_Alarm/README.md) | E-bike alarm combining vibration detection, wireless input, and a buzzer. |

### 10–19: Time Base, Display, and PWM

| No. | Project | Description |
|---:|---|---|
| 10 | [Custom_Delay](10_Custom_Delay/README.md) | Custom microsecond and millisecond delays based on SysTick. |
| 11 | [Custom_OS_Delay](11_Custom_OS_Delay/README.md) | Delay functions designed to coexist with a system tick. |
| 12 | [SysTick_Multitasking](12_SysTick_Multitasking/README.md) | SysTick counters and flags used to simulate periodic tasks. |
| 13 | [Infrared_Module](13_Infrared_Module/README.md) | Infrared module digital input and application response. |
| 14 | [LCD1602_Character](14_LCD1602_Character/README.md) | LCD1602 initialization, cursor positioning, and single-character output. |
| 15 | [LCD1602_String](15_LCD1602_String/README.md) | String output on an LCD1602. |
| 16 | [Queue_System_Framework](16_Queue_System_Framework/README.md) | Module and program framework for a queue-calling system. |
| 17 | [Queue_System](17_Queue_System/README.md) | Queue control using buttons, display output, and queue logic. |
| 18 | [Timer_Interrupt_LED](18_Timer_Interrupt_LED/README.md) | Periodic timer interrupts and LED toggling. |
| 19 | [PWM_Breathing_LED](19_PWM_Breathing_LED/README.md) | Breathing LED effect produced by varying PWM duty cycle. |

### 20–29: Capture, Measurement, and Watchdogs

| No. | Project | Description |
|---:|---|---|
| 20 | [UART_Print](20_UART_Print/README.md) | Debug UART initialization and `printf()` redirection. |
| 21 | [Input_Capture](21_Input_Capture/README.md) | Basic timer input-capture configuration and edge timing. |
| 22 | [Button_Press_Capture](22_Button_Press_Capture/README.md) | Complete button pulse measurement with input capture. |
| 23 | [Button_Press_Duration](23_Button_Press_Duration/README.md) | Button press duration calculated from captured timestamps. |
| 24 | [Pulse_Count](24_Pulse_Count/README.md) | External pulse detection and counting. |
| 25 | [SG90_Servo](25_SG90_Servo/README.md) | SG90 servo angle control with PWM. |
| 26 | [Ultrasonic_Sensor](26_Ultrasonic_Sensor/README.md) | HC-SR04 triggering, echo timing, and distance calculation. |
| 27 | [Touchless_Trash_Can](27_Touchless_Trash_Can/README.md) | Touchless lid control using ultrasonic ranging and a servo. |
| 28 | [Independent_Watchdog](28_Independent_Watchdog/README.md) | Independent watchdog setup, refresh, and reset verification. |
| 29 | [Window_Watchdog](29_Window_Watchdog/README.md) | Window watchdog refresh timing and abnormal-reset behavior. |

### 30–40: UART, Bluetooth, Wi-Fi, and 4G

| No. | Project | Description |
|---:|---|---|
| 30 | [UART_Character_TX_RX](30_UART_Character_TX_RX/README.md) | UART single-character transmission, reception, and echo. |
| 31 | [UART_Variable_Length_RX_Interrupt](31_UART_Variable_Length_RX_Interrupt/README.md) | Variable-length UART input handled with receive interrupts. |
| 32 | [UART_Variable_Length_Idle_Interrupt](32_UART_Variable_Length_Idle_Interrupt/README.md) | UART idle-line detection used to delimit variable-length frames. |
| 33 | [Bluetooth_Module](33_Bluetooth_Module/README.md) | Transparent serial communication through a Bluetooth module. |
| 34 | [Bluetooth_Relay_Outlet](34_Bluetooth_Relay_Outlet/README.md) | Relay outlet controlled by phone commands over Bluetooth. |
| 35 | [ESP8266_UART](35_ESP8266_UART/README.md) | AT-command UART communication between STM32 and ESP8266. |
| 36 | [ESP8266_WiFi](36_ESP8266_WiFi/README.md) | ESP8266 Station mode and Wi-Fi connection. |
| 37 | [ESP8266_TCP_Client](37_ESP8266_TCP_Client/README.md) | ESP8266 TCP client connection and data exchange. |
| 38 | [ESP8266_TCP_Server](38_ESP8266_TCP_Server/README.md) | ESP8266 TCP server and incoming client connections. |
| 39 | [WiFi_Relay_Fan](39_WiFi_Relay_Fan/README.md) | Remote relay fan control through Wi-Fi commands. |
| 40 | [4G_LED_Control](40_4G_LED_Control/README.md) | Remote LED control over a 4G transparent data link. |

### 41–50: DMA, ADC, Display, and Storage

| No. | Project | Description |
|---:|---|---|
| 41 | [DMA_Memory_to_Memory](41_DMA_Memory_to_Memory/README.md) | Data copy between two memory areas using DMA. |
| 42 | [DMA_Memory_to_Peripheral](42_DMA_Memory_to_Peripheral/README.md) | DMA transfer from memory to a peripheral. |
| 43 | [DMA_Peripheral_to_Memory](43_DMA_Peripheral_to_Memory/README.md) | DMA reception from a peripheral into a memory buffer. |
| 44 | [ADC_Single_Channel](44_ADC_Single_Channel/README.md) | Single-channel ADC polling and voltage conversion. |
| 45 | [ADC_Single_Channel_DMA](45_ADC_Single_Channel_DMA/README.md) | Automatic DMA transfer of single-channel ADC samples. |
| 46 | [ADC_Multi_Channel_DMA](46_ADC_Multi_Channel_DMA/README.md) | Multi-channel ADC scanning with DMA result storage. |
| 47 | [Smoking_Room_System](47_Smoking_Room_System/README.md) | Integrated gas sensing, alarm, and ventilation control. |
| 48 | [OLED](48_OLED/README.md) | OLED initialization and character, string, and numeric output. |
| 49 | [W25Q128_Read_Write](49_W25Q128_Read_Write/README.md) | SPI read, program, and erase operations for W25Q128 flash. |
| 50 | [Matrix_Keypad](50_Matrix_Keypad/README.md) | Row/column scanning and key identification for a 4×4 keypad. |

### 51–61: System Features, Sensors, and IoT

| No. | Project | Description |
|---:|---|---|
| 51 | [Smart_Access_Control](51_Smart_Access_Control/README.md) | Smart access control with keypad, OLED, password storage, and lock. |
| 52 | [BKP_Read_Write](52_BKP_Read_Write/README.md) | Backup domain and BKP register retention. |
| 53 | [RTC_Read_Write](53_RTC_Read_Write/README.md) | RTC time setting, reading, and UART output. |
| 54 | [RTC_Alarm](54_RTC_Alarm/README.md) | RTC alarm configuration and interrupt response. |
| 55 | [Real_Time_Clock](55_Real_Time_Clock/README.md) | Complete real-time clock display and timekeeping exercise. |
| 56 | [Low_Power](56_Low_Power/README.md) | STM32 sleep, stop, standby, and related low-power modes. |
| 57 | [CAN_TX_RX](57_CAN_TX_RX/README.md) | CAN frame transmission, reception, and internal loopback test. |
| 58 | [DHT11](58_DHT11/README.md) | DHT11 single-wire timing and temperature/humidity readout. |
| 59 | [OneNET_Temp_Humidity](59_OneNET_Temp_Humidity/README.md) | ESP8266, MQTT, and temperature/humidity uploads to OneNET. |
| 60 | [Weather_Forecast](60_Weather_Forecast/README.md) | Retrieval, parsing, and OLED display of a three-day forecast. |
| 61 | [Smart_Desk_Lamp](61_Smart_Desk_Lamp/README.md) | Automatic dimming, posture reminder, timer, and Bluetooth lamp control. |

### 62–74: Smart Cars

| No. | Project | Description |
|---:|---|---|
| 62 | [Car_Movement](62_Car_Movement/README.md) | Two-wheel car movement: forward, backward, turning, and stop. |
| 63 | [UART_Controlled_Car](63_UART_Controlled_Car/README.md) | Car controlled by USART2 text commands. |
| 64 | [Bluetooth_Controlled_Car](64_Bluetooth_Controlled_Car/README.md) | Wireless car control through a Bluetooth serial module. |
| 65 | [Jog_Controlled_Car](65_Jog_Controlled_Car/README.md) | Momentary control where each command produces a short movement. |
| 66 | [PWM_Speed_Control_Car](66_PWM_Speed_Control_Car/README.md) | Dual-wheel PWM speed adjustment and differential steering. |
| 67A | [Line_Tracking_Car](67_Line_Tracking_Car/README.md) | Fixed-speed line tracking with two infrared sensors. |
| 67B | [Line_Tracking_PWM](67_Line_Tracking_PWM/README.md) | Dual-sensor tracking with independent wheel PWM. |
| 68 | [Object_Following_Car](68_Object_Following_Car/README.md) | Simple object following with two infrared detectors. |
| 69 | [Obstacle_Avoidance_Car](69_Obstacle_Avoidance_Car/README.md) | Servo-mounted ultrasonic scanning and turn-direction selection. |
| 70 | [Car_Speed_Measurement](70_Car_Speed_Measurement/README.md) | Wheel sensor pulse counting over a fixed measurement window. |
| 71 | [Car_Speed_OLED_Bluetooth](71_Car_Speed_OLED_Bluetooth/README.md) | Speed result shown on an OLED and sent over Bluetooth. |
| 72 | [WiFi_Car_Speed_Report](72_WiFi_Car_Speed_Report/README.md) | Wi-Fi car control and speed-data reporting to a server. |
| 73 | [4G_Controlled_Car](73_4G_Controlled_Car/README.md) | 4G transparent control and remote speed reporting. |
| 74 | [Voice_Controlled_Car](74_Voice_Controlled_Car/README.md) | Voice-code input and a framework for tracking, following, and avoidance modes. |

### 75–84: Integrated Projects, MPU6050, and Balancing Car

| No. | Project | Description |
|---:|---|---|
| 75 | [Smart_Home_ZET6](75_Smart_Home_ZET6/README.md) | ZET6 smart-home integration; the active entry mainly tests W25Q128. |
| 76 | [Smart_Home_NB_ZET6](76_Smart_Home_NB_ZET6/README.md) | Integrated password access, environmental control, and MQTT connectivity. |
| 77 | [MPU6050_Register_Read_Write](77_MPU6050_Register_Read_Write/README.md) | Single-register MPU6050 access through GPIO software I2C. |
| 78 | [MPU6050_Burst_Read_Write](78_MPU6050_Burst_Read_Write/README.md) | Burst access to consecutive MPU6050 registers. |
| 79 | [MPU6050_Data_Read](79_MPU6050_Data_Read/README.md) | Raw three-axis acceleration, temperature, and gyroscope readout. |
| 80 | [MPU6050_eMPL](80_MPU6050_eMPL/README.md) | Polled MPU6050 DMP pitch, roll, and yaw output. |
| 81 | [MPU6050_eMPL_INT](81_MPU6050_eMPL_INT/README.md) | DMP readout triggered by the MPU6050 data-ready interrupt. |
| 82 | [Encoder_Test](82_Encoder_Test/README.md) | Timer quadrature encoder mode and count-delta measurement. |
| 83 | [TB6612_Motor_Driver](83_TB6612_Motor_Driver/README.md) | TB6612 dual-motor direction control, PWM, and test interfaces. |
| 84 | [PID_Balancing_Car](84_PID_Balancing_Car/README.md) | Two-wheel balancing car combining DMP, encoders, Bluetooth, and multi-loop control. |

## Repository Layout

Most projects use a similar directory layout, although early and integrated projects may differ slightly:

```text
My_MCU_Stage1_Labs_Archive/
├── README.md                 # English repository guide
├── README_zh.md              # Chinese repository guide
├── 00_STM32F103C8T6_Template/
│   ├── README.md             # Project guide in English
│   ├── README_zh.md          # Project guide in Chinese
│   ├── Drivers/              # CMSIS, HAL, system, and BSP drivers
│   ├── Projects/MDK-ARM/     # Keil project and debug configuration
│   ├── Users/                # main.c, interrupts, and user configuration
│   └── Output/               # Historical build artifacts retained by some projects
├── 01_LED/
└── ...
```

The subprojects are not built together as one monolithic application. Each directory has its own startup code, HAL/CMSIS files, BSP modules, user code, and Keil configuration, and must be opened and built separately.

## Quick Start

1. Clone or download this repository.
2. Select an experiment from the index and read its `README.md` first.
3. Verify the MCU model, module power, GPIO, UART, timer, and external-interrupt wiring.
4. Open the `.uvprojx` file under that project's `Projects/MDK-ARM` directory with Keil MDK.
5. Install the required STM32F1 Device Family Pack and select an available ARM compiler.
6. Build the project and flash it with ST-Link, J-Link, or another compatible probe.
7. Observe low-risk outputs such as UART, LEDs, or the OLED before connecting relays, motors, servos, or other actuators.

Many projects use a 115200-baud debug UART, but this is not universal. Check the UART initialization in the selected project.

## Notes on Reading and Reproducing the Labs

- This source is a staged learning record, not a single standardized architecture or production-ready codebase.
- Some projects deliberately use blocking delays, application logic inside interrupts, fixed-length buffers, or simplified state machines to focus on a specific topic.
- A few integrated projects retain disabled functions, commented test entries, or partially completed frameworks. Each project README describes what the active `main.c` currently does.
- Some car projects label a value as `speed` even though it is still a raw pulse count over a fixed time window. It has not yet been calibrated using wheel circumference, encoder resolution, and gearbox ratio.
- The CAN project currently focuses on internal loopback, while the voice-controlled car focuses on command-code input and a multi-mode framework. These states are intentionally preserved from the original learning stage.

## Hardware Safety

- MCU GPIO cannot directly drive motors, relay coils, or other high-current loads. Use a suitable driver circuit or module.
- Motors and servos should use an adequately rated external supply, with the control system grounded correctly.
- Confirm compatibility between 3.3 V and 5 V logic. Use a divider or level shifter when required.
- Raise the wheels before testing a car. Secure a balancing-car chassis and keep a way to disconnect motor power immediately.
- Controlling mains voltage with relays creates shock and fire hazards. These labs are intended for low-voltage learning and should not be connected to mains loads without proper isolation, protection, and qualified supervision.

## Disclaimer

This repository is primarily a personal learning record, code backup, and experiment archive. Hardware wiring, module revisions, Keil software packs, and compiler versions can all affect the result. Before running any project again, read its README and source code and verify every parameter against the hardware currently in use.
