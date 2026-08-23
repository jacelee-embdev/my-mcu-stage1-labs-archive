**简体中文** | [English](README.md)

# STM32F103C8T6 自定义延时函数

## 项目简介

本工程用于学习基于 Cortex-M3 SysTick 定时器手动实现阻塞式延时。代码直接配置 SysTick 的重装值、当前计数值和控制寄存器，提供微秒、毫秒和秒级接口，并重写 HAL 的 `HAL_Delay()`。

## 主要内容

- `delay_us()` 按 72 MHz 时钟计算所需计数周期。
- `delay_ms()` 和 `delay_s()` 在微秒延时基础上逐级封装。
- 延时期间 CPU 忙等待，适用于简单裸机实验。

## 运行说明

当前 `main.c` 只完成 HAL 和 72 MHz 系统时钟初始化，主循环为空，工程重点是保存延时函数的底层实现。测试时可在主循环中加入 GPIO 翻转，并使用 `delay_ms()` 控制间隔。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，编译下载或单步观察 SysTick 寄存器。

## 主要文件

- `Drivers/SYSTEM/delay/delay.c`：自定义延时实现。
- `Users/main.c`：最小运行入口。

