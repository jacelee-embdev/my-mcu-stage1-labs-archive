**简体中文** | [English](README.md)

# STM32F103C8T6 定时器中断点灯

## 项目简介

本工程演示 TIM2 基本定时器更新中断。程序将 TIM2 配置为向上计数并开启更新中断，在 HAL 周期回调中翻转 LED1，主循环无需执行闪灯延时。

## 主要功能

- 初始化 TIM2、时钟和 NVIC 中断。
- 使用预分频值 7199、自动重装值 4999。
- 在 72 MHz 定时器时钟下约每 500 ms 产生一次更新事件。
- 每次中断翻转 PB8 上的 LED1。

## 运行现象

程序下载后，LED1 以约 1 秒为一个完整明暗周期持续闪烁。该实验展示了硬件定时器相对阻塞式延时的独立计时能力。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，编译下载后观察 LED。可修改 `timer_init()` 的参数改变中断周期。

## 主要文件

- `Drivers/BSP/timer/timer.c`：TIM2 初始化、ISR 和回调。
- `Users/main.c`：外设初始化入口。

