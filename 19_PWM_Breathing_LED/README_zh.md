**简体中文** | [English](README.md)

# STM32F103C8T6 PWM 呼吸灯

## 项目简介

本工程使用 TIM4 通道 3 输出 PWM，逐步改变 LED 占空比，实现亮度缓慢升降的呼吸效果。PB8 配置为复用推挽输出，主循环通过修改比较寄存器控制 PWM 脉宽。

## 主要功能

- 配置 TIM4_CH3 在 PB8 输出 PWM。
- 使用预分频值 71、自动重装值 499，PWM 频率约为 2 kHz。
- 比较值在 0–299 之间递增、递减，每步延时 10 ms。
- 封装 `set_pwm_compare()` 便于动态调整占空比。

## 运行现象

连接在 PB8 的低电平有效 LED 会反复渐亮、渐暗，完成一次升降约需 6 秒。实际亮度范围受比较值和 LED 驱动电路影响。

## 使用方法

使用 Keil MDK 打开 `Projects/MDK-ARM/stm32f103.uvprojx`，编译下载后观察 LED。可修改比较值范围或步进延时调整呼吸速度和亮度范围。

## 主要文件

- `Drivers/BSP/pwm_led/`：TIM4 PWM 驱动。
- `Users/main.c`：占空比渐变逻辑。

