**简体中文** | [English](README.md)

# My MCU Stage 1 Labs Archive

STM32F1 单片机第一阶段学习实验归档，包含从 GPIO、定时器、串口和 DMA，到传感器、物联网、智能小车及 PID 平衡控制的 86 个独立工程。

## 仓库简介

这个仓库用于保存第一阶段 MCU 学习过程中积累的实验代码和学习记录。它首先是一份个人学习归档和云端备份：当本地代码丢失、更换电脑，或需要重新连接硬件验证某个知识点时，可以直接拉取对应工程继续使用。

仓库中的工程按学习顺序编号，彼此独立，可以单独打开、编译和下载。代码保留了当时的实现方式、调试过程和阶段性状态，因此其中既有完整应用，也有只验证某个外设或通信流程的小实验。每个子工程都提供简短的中英文 README，用于说明当前程序实际做什么、涉及哪些模块，以及再次运行时需要注意什么。

## 归档概况

| 项目 | 说明 |
|---|---|
| 工程数量 | 86 个独立实验工程 |
| 编号范围 | `00`–`84`；编号 `67` 包含两个不同版本 |
| 主要 MCU | STM32F103C8T6；综合实验 `75`、`76` 使用 STM32F103ZET6 |
| 开发语言 | C |
| 软件框架 | STM32 HAL、CMSIS，以及各实验自编 BSP 驱动 |
| 开发环境 | Keil MDK 5，工程文件为 `.uvprojx` |
| 下载调试 | ST-Link、J-Link 或其他兼容 SWD 调试器 |
| 文档语言 | `README.md` 为英文，`README_zh.md` 为简体中文 |

多数 STM32F103 工程将系统主频配置为 72 MHz。具体引脚、串口、定时器、外设参数和当前运行行为，请以对应子工程的 README 与源代码为准。

## 学习内容

这批工程大致覆盖以下学习阶段：

| 阶段 | 工程范围 | 主要内容 |
|---|---|---|
| 基础输入输出 | 00–09 | 工程模板、LED、按键、外部中断、蜂鸣器、继电器及简单报警应用 |
| 时基与基础人机交互 | 10–19 | 延时、SysTick、任务调度、红外输入、LCD1602、定时器和 PWM |
| 定时器测量与系统保护 | 20–29 | 串口打印、输入捕获、脉冲计数、舵机、超声波和看门狗 |
| 串口与无线通信 | 30–40 | 不定长串口接收、蓝牙、ESP8266、TCP、Wi-Fi 和 4G 透传 |
| 数据采集与常用外设 | 41–50 | DMA、ADC、OLED、W25Q128、矩阵键盘及综合传感应用 |
| RTC、低功耗与物联网 | 51–61 | 门禁、备份域、实时时钟、低功耗、CAN、DHT11、OneNET、天气和智能台灯 |
| 智能小车 | 62–74 | 基础运动、无线遥控、PWM、循迹、跟随、避障、测速和多模式控制 |
| 综合控制 | 75–84 | 智能家居、MPU6050、DMP、编码器、TB6612 和两轮 PID 平衡车 |

## 完整实验索引

单击工程名称可直接查看对应的中文说明。

| 编号 | 工程 | 内容 |
|---:|---|---|
| 00 | [STM32F103C8T6_Template](00_STM32F103C8T6_Template/README_zh.md) | 可复用的 STM32F103C8T6 HAL 基础工程模板。 |
| 01 | [LED](01_LED/README_zh.md) | GPIO 推挽输出与单个 LED 点亮、翻转。 |
| 02 | [LED_Chaser](02_LED_Chaser/README_zh.md) | 多个 LED 按顺序点亮，形成流水灯效果。 |
| 03 | [Buzzer](03_Buzzer/README_zh.md) | GPIO 控制蜂鸣器发声与关闭。 |
| 04 | [Button](04_Button/README_zh.md) | 按键 GPIO 输入、状态读取和简单消抖。 |
| 05 | [Interrupt](05_Interrupt/README_zh.md) | GPIO 外部中断、NVIC 和中断回调。 |
| 06 | [Vibration_LED](06_Vibration_LED/README_zh.md) | 振动传感器触发 LED，用于验证数字输入。 |
| 07 | [Relay](07_Relay/README_zh.md) | 使用 GPIO 控制继电器吸合与释放。 |
| 08 | [433MHz_RF](08_433MHz_RF/README_zh.md) | 433 MHz 无线接收模块的数据检测实验。 |
| 09 | [Electric_Bike_Alarm](09_Electric_Bike_Alarm/README_zh.md) | 组合振动检测、无线输入和蜂鸣器的电动车报警器。 |
| 10 | [Custom_Delay](10_Custom_Delay/README_zh.md) | 基于 SysTick 编写自定义微秒、毫秒延时。 |
| 11 | [Custom_OS_Delay](11_Custom_OS_Delay/README_zh.md) | 实现与系统节拍共存的延时函数。 |
| 12 | [SysTick_Multitasking](12_SysTick_Multitasking/README_zh.md) | 使用 SysTick 计数和标志位模拟周期任务。 |
| 13 | [Infrared_Module](13_Infrared_Module/README_zh.md) | 读取红外模块数字输出并执行响应。 |
| 14 | [LCD1602_Character](14_LCD1602_Character/README_zh.md) | LCD1602 初始化、定位和单字符显示。 |
| 15 | [LCD1602_String](15_LCD1602_String/README_zh.md) | 在 LCD1602 上显示字符串。 |
| 16 | [Queue_System_Framework](16_Queue_System_Framework/README_zh.md) | 排队叫号系统的模块与程序框架。 |
| 17 | [Queue_System](17_Queue_System/README_zh.md) | 按键、显示和队列逻辑组成的排队控制实验。 |
| 18 | [Timer_Interrupt_LED](18_Timer_Interrupt_LED/README_zh.md) | 定时器周期中断与 LED 翻转。 |
| 19 | [PWM_Breathing_LED](19_PWM_Breathing_LED/README_zh.md) | 通过 PWM 占空比渐变实现呼吸灯。 |
| 20 | [UART_Print](20_UART_Print/README_zh.md) | 初始化调试串口并重定向 `printf()`。 |
| 21 | [Input_Capture](21_Input_Capture/README_zh.md) | 定时器输入捕获的基础配置与边沿测量。 |
| 22 | [Button_Press_Capture](22_Button_Press_Capture/README_zh.md) | 使用输入捕获记录完整的按键脉冲。 |
| 23 | [Button_Press_Duration](23_Button_Press_Duration/README_zh.md) | 根据捕获时间计算按键按下时长。 |
| 24 | [Pulse_Count](24_Pulse_Count/README_zh.md) | 外部脉冲检测与计数。 |
| 25 | [SG90_Servo](25_SG90_Servo/README_zh.md) | PWM 控制 SG90 舵机转角。 |
| 26 | [Ultrasonic_Sensor](26_Ultrasonic_Sensor/README_zh.md) | HC-SR04 触发、回波计时与距离计算。 |
| 27 | [Touchless_Trash_Can](27_Touchless_Trash_Can/README_zh.md) | 超声波测距配合舵机实现感应开盖。 |
| 28 | [Independent_Watchdog](28_Independent_Watchdog/README_zh.md) | 独立看门狗初始化、喂狗和复位验证。 |
| 29 | [Window_Watchdog](29_Window_Watchdog/README_zh.md) | 窗口看门狗刷新时机与异常复位。 |
| 30 | [UART_Character_TX_RX](30_UART_Character_TX_RX/README_zh.md) | 串口单字符发送、接收和回显。 |
| 31 | [UART_Variable_Length_RX_Interrupt](31_UART_Variable_Length_RX_Interrupt/README_zh.md) | 使用接收中断处理不定长串口数据。 |
| 32 | [UART_Variable_Length_Idle_Interrupt](32_UART_Variable_Length_Idle_Interrupt/README_zh.md) | 使用串口空闲中断划分不定长数据帧。 |
| 33 | [Bluetooth_Module](33_Bluetooth_Module/README_zh.md) | 蓝牙串口模块的透明传输测试。 |
| 34 | [Bluetooth_Relay_Outlet](34_Bluetooth_Relay_Outlet/README_zh.md) | 手机蓝牙命令控制继电器插座。 |
| 35 | [ESP8266_UART](35_ESP8266_UART/README_zh.md) | STM32 与 ESP8266 的 AT 串口通信。 |
| 36 | [ESP8266_WiFi](36_ESP8266_WiFi/README_zh.md) | ESP8266 Station 模式连接 Wi-Fi。 |
| 37 | [ESP8266_TCP_Client](37_ESP8266_TCP_Client/README_zh.md) | ESP8266 建立 TCP 客户端连接并收发数据。 |
| 38 | [ESP8266_TCP_Server](38_ESP8266_TCP_Server/README_zh.md) | ESP8266 建立 TCP 服务器并接收客户端连接。 |
| 39 | [WiFi_Relay_Fan](39_WiFi_Relay_Fan/README_zh.md) | 通过 Wi-Fi 命令远程控制继电器风扇。 |
| 40 | [4G_LED_Control](40_4G_LED_Control/README_zh.md) | 使用 4G 透明传输链路远程控制 LED。 |
| 41 | [DMA_Memory_to_Memory](41_DMA_Memory_to_Memory/README_zh.md) | 使用 DMA 在两块内存之间复制数据。 |
| 42 | [DMA_Memory_to_Peripheral](42_DMA_Memory_to_Peripheral/README_zh.md) | DMA 将内存数据传输到外设。 |
| 43 | [DMA_Peripheral_to_Memory](43_DMA_Peripheral_to_Memory/README_zh.md) | DMA 接收外设数据到内存缓冲区。 |
| 44 | [ADC_Single_Channel](44_ADC_Single_Channel/README_zh.md) | ADC 单通道轮询采样与电压换算。 |
| 45 | [ADC_Single_Channel_DMA](45_ADC_Single_Channel_DMA/README_zh.md) | ADC 单通道配合 DMA 自动搬运结果。 |
| 46 | [ADC_Multi_Channel_DMA](46_ADC_Multi_Channel_DMA/README_zh.md) | ADC 扫描多个通道并由 DMA 保存数据。 |
| 47 | [Smoking_Room_System](47_Smoking_Room_System/README_zh.md) | 气体检测、报警和排风控制的综合实验。 |
| 48 | [OLED](48_OLED/README_zh.md) | OLED 初始化、字符、字符串和数字显示。 |
| 49 | [W25Q128_Read_Write](49_W25Q128_Read_Write/README_zh.md) | 通过 SPI 读写、擦除 W25Q128 Flash。 |
| 50 | [Matrix_Keypad](50_Matrix_Keypad/README_zh.md) | 4×4 矩阵键盘的行列扫描与按键识别。 |
| 51 | [Smart_Access_Control](51_Smart_Access_Control/README_zh.md) | 键盘、OLED、密码存储和门锁组成的智能门禁。 |
| 52 | [BKP_Read_Write](52_BKP_Read_Write/README_zh.md) | 备份域与 BKP 寄存器掉电保持实验。 |
| 53 | [RTC_Read_Write](53_RTC_Read_Write/README_zh.md) | RTC 时间设置、读取和串口显示。 |
| 54 | [RTC_Alarm](54_RTC_Alarm/README_zh.md) | RTC 闹钟配置与中断响应。 |
| 55 | [Real_Time_Clock](55_Real_Time_Clock/README_zh.md) | 实时时钟显示和时间维护的完整练习。 |
| 56 | [Low_Power](56_Low_Power/README_zh.md) | STM32 睡眠、停止和待机等低功耗模式。 |
| 57 | [CAN_TX_RX](57_CAN_TX_RX/README_zh.md) | CAN 报文发送、接收与内部环回验证。 |
| 58 | [DHT11](58_DHT11/README_zh.md) | DHT11 单总线时序及温湿度读取。 |
| 59 | [OneNET_Temp_Humidity](59_OneNET_Temp_Humidity/README_zh.md) | ESP8266、MQTT 和 OneNET 温湿度上报。 |
| 60 | [Weather_Forecast](60_Weather_Forecast/README_zh.md) | 获取、解析并在 OLED 显示未来三天天气。 |
| 61 | [Smart_Desk_Lamp](61_Smart_Desk_Lamp/README_zh.md) | 自动调光、坐姿提醒、计时和蓝牙控制台灯。 |
| 62 | [Car_Movement](62_Car_Movement/README_zh.md) | 两轮小车前进、后退、转向和停止。 |
| 63 | [UART_Controlled_Car](63_UART_Controlled_Car/README_zh.md) | 使用 USART2 文本命令控制小车。 |
| 64 | [Bluetooth_Controlled_Car](64_Bluetooth_Controlled_Car/README_zh.md) | 通过蓝牙串口模块遥控小车。 |
| 65 | [Jog_Controlled_Car](65_Jog_Controlled_Car/README_zh.md) | 每条命令只执行短时间动作的点动控制。 |
| 66 | [PWM_Speed_Control_Car](66_PWM_Speed_Control_Car/README_zh.md) | 双路 PWM 调速与差速转向。 |
| 67A | [Line_Tracking_Car](67_Line_Tracking_Car/README_zh.md) | 双路红外传感器与固定速度循迹。 |
| 67B | [Line_Tracking_PWM](67_Line_Tracking_PWM/README_zh.md) | 加入左右轮 PWM 的双路循迹版本。 |
| 68 | [Object_Following_Car](68_Object_Following_Car/README_zh.md) | 双路红外检测实现简单目标跟随。 |
| 69 | [Obstacle_Avoidance_Car](69_Obstacle_Avoidance_Car/README_zh.md) | 舵机带动超声波扫描左右并选择转向。 |
| 70 | [Car_Speed_Measurement](70_Car_Speed_Measurement/README_zh.md) | 在固定时间窗内统计车轮测速脉冲。 |
| 71 | [Car_Speed_OLED_Bluetooth](71_Car_Speed_OLED_Bluetooth/README_zh.md) | 测速结果通过 OLED 显示并由蓝牙发送。 |
| 72 | [WiFi_Car_Speed_Report](72_WiFi_Car_Speed_Report/README_zh.md) | Wi-Fi 控制小车并向服务器上报测速数据。 |
| 73 | [4G_Controlled_Car](73_4G_Controlled_Car/README_zh.md) | 4G 透明传输远程控制和测速回传。 |
| 74 | [Voice_Controlled_Car](74_Voice_Controlled_Car/README_zh.md) | 语音码读取及循迹、跟随、避障模式框架。 |
| 75 | [Smart_Home_ZET6](75_Smart_Home_ZET6/README_zh.md) | ZET6 智能家居模块集成；当前入口主要测试 W25Q128。 |
| 76 | [Smart_Home_NB_ZET6](76_Smart_Home_NB_ZET6/README_zh.md) | 密码门禁、环境控制和 MQTT 联网集成版。 |
| 77 | [MPU6050_Register_Read_Write](77_MPU6050_Register_Read_Write/README_zh.md) | GPIO 模拟 I2C 的 MPU6050 单寄存器读写。 |
| 78 | [MPU6050_Burst_Read_Write](78_MPU6050_Burst_Read_Write/README_zh.md) | MPU6050 连续寄存器突发读写。 |
| 79 | [MPU6050_Data_Read](79_MPU6050_Data_Read/README_zh.md) | 读取三轴加速度、温度和三轴陀螺仪原始值。 |
| 80 | [MPU6050_eMPL](80_MPU6050_eMPL/README_zh.md) | 轮询 MPU6050 DMP，输出俯仰、横滚和偏航角。 |
| 81 | [MPU6050_eMPL_INT](81_MPU6050_eMPL_INT/README_zh.md) | 使用 MPU6050 数据就绪中断触发 DMP 读取。 |
| 82 | [Encoder_Test](82_Encoder_Test/README_zh.md) | 定时器正交编码器模式与计数增量读取。 |
| 83 | [TB6612_Motor_Driver](83_TB6612_Motor_Driver/README_zh.md) | TB6612 双电机方向控制、PWM 调速和测试接口。 |
| 84 | [PID_Balancing_Car](84_PID_Balancing_Car/README_zh.md) | DMP、编码器、蓝牙和多环控制组成的两轮平衡车。 |

## 目录结构

各工程通常采用相近的目录布局，但早期和综合工程之间可能略有差异：

```text
My_MCU_Stage1_Labs_Archive/
├── README.md                 # English repository guide
├── README_zh.md              # 中文仓库说明
├── 00_STM32F103C8T6_Template/
│   ├── README.md             # 子工程英文说明
│   ├── README_zh.md          # 子工程中文说明
│   ├── Drivers/              # CMSIS、HAL、系统与 BSP 驱动
│   ├── Projects/MDK-ARM/     # Keil 工程和调试配置
│   ├── Users/                # main.c、中断与用户配置
│   └── Output/               # 部分工程保留的历史编译产物
├── 01_LED/
└── ...
```

这些子工程不是一个统一编译的单体项目。每个目录都有自己的启动文件、HAL/CMSIS、BSP、用户代码和 Keil 配置，应分别打开和编译。

## 快速开始

1. 克隆或下载本仓库。
2. 根据上面的索引选择实验，先阅读该目录中的 `README_zh.md`。
3. 核对 MCU 型号、模块供电、GPIO、串口、定时器和外部中断接线。
4. 使用 Keil MDK 打开该目录 `Projects/MDK-ARM` 下的 `.uvprojx` 文件。
5. 安装工程所需的 STM32F1 Device Family Pack，并选择可用的 ARM 编译器。
6. 编译工程，通过 ST-Link、J-Link 或兼容调试器下载到开发板。
7. 先观察串口、LED 或 OLED 等低风险输出，再接入继电器、电机、舵机等执行器。

许多工程使用 115200 波特率输出调试信息，但并非全部如此。请以对应串口初始化代码为准。

## 阅读与复现实验时的说明

- 这些代码是学习过程的阶段性记录，不代表统一的软件架构或生产级实现。
- 部分工程为了突出知识点，使用阻塞延时、在中断中处理业务、固定长度缓冲区或简化的状态机。
- 个别综合工程保留了尚未启用的函数、注释掉的测试入口，或只完成了框架。子工程 README 会说明当前 `main.c` 实际运行的行为。
- 小车测速工程中的部分 `speed` 值仍是固定时间窗内的原始脉冲数，尚未根据轮径、编码器线数和减速比标定为真实物理速度。
- CAN 工程当前以内部环回为主；语音小车当前以语音码读取和模式框架为主；这些状态均属于原学习阶段的真实记录。

## 硬件安全

- MCU GPIO 不能直接驱动电机、继电器线圈或其他大电流负载，必须使用合适的驱动模块。
- 电机和舵机建议使用独立且容量足够的电源，并与 MCU 控制系统正确共地。
- 确认 3.3 V 与 5 V 模块的逻辑电平兼容，必要时使用分压或电平转换。
- 调试小车时先架空车轮；调试平衡车时固定车体，并准备随时断开电机电源。
- 继电器控制市电存在触电和火灾风险。本仓库实验仅用于低压学习验证，不建议在缺少隔离和保护的情况下连接市电负载。

## 说明

本仓库主要用于个人学习记录、代码备份和实验复现。硬件接线、模块版本、Keil 软件包和编译器差异都可能影响结果。重新运行任何工程前，请先阅读对应 README 和源代码，并根据当前硬件重新核对参数。
