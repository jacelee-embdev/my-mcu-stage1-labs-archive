**简体中文** | [English](README.md)

# STM32F103C8T6 兼容系统节拍的延时函数

## 项目简介

本工程改进 SysTick 延时方式，使延时函数在 SysTick 已经作为系统节拍运行时仍可使用。它不重新装载或停止 SysTick，而是持续读取递减计数值并累计经过的时钟周期，因此不会破坏原有节拍配置。

## 主要内容

- 根据 72 MHz 主频实现微秒级忙等待。
- 正确处理 SysTick 计数器重装时的回绕。
- 在 `delay_us()` 基础上封装毫秒、秒和 `HAL_Delay()`。
- 示例使用两路 LED 验证延时接口。

## 运行说明

主循环先设置 LED1 亮、LED2 灭并延时 500 ms，再交换状态；代码中第二处延时目前被注释，因此两种状态的保持时间并不对称。工程重点是延时算法本身，而不是完整任务调度器。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，编译下载后观察 LED，或单步查看 SysTick 计数变化。

## 主要文件

- `Drivers/SYSTEM/delay/delay.c`：兼容运行中 SysTick 的延时实现。
- `Users/main.c`：LED 测试入口。

