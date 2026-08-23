/**
 * @file    encoder.h
 * @brief   正交编码器驱动头文件 - 提供计数获取与硬件初始化接口
 */

#ifndef __ENCODER_H__
#define __ENCODER_H__

/* Includes ------------------------------------------------------------------*/
#include "sys.h"

/* [硬件移植区] --------------------------------------------------------------*/
#define ENCODER_TIM                  TIM4                                       // 编码器接口所使用的定时器实例
#define ENCODER_TIM_CLK_ENABLE()     __HAL_RCC_TIM4_CLK_ENABLE()                // 定时器时钟使能宏

#define ENCODER_GPIO_PORT            GPIOB                                      // 编码器引脚所属端口
#define ENCODER_GPIO_CLK_ENABLE()    __HAL_RCC_GPIOB_CLK_ENABLE()               // GPIO 时钟使能宏
#define ENCODER_PIN_A                GPIO_PIN_6                                 // 编码器 A 相引脚
#define ENCODER_PIN_B                GPIO_PIN_7                                 // 编码器 B 相引脚

/* [配置参数区] --------------------------------------------------------------*/
#define ENCODER_RELOAD_VALUE         ((uint32_t)65535)                          // 16位计数器自动重装载值 (65536-1)
#define ENCODER_IC_FILTER            ((uint8_t)0x0A)                            // 输入捕获滤波器配置 (10个采样周期)

/* [功能接口声明] ------------------------------------------------------------*/
void    encoder_init(void);                                                     // 初始化正交编码器接口硬件配置
int16_t encoder_get_count_delta(void);                                          // 获取当前增量计数值并清零计数器

#endif /* __ENCODER_H__ */
