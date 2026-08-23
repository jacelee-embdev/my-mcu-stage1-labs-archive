/**
 * @file    encoder.h
 * @brief   正交编码器驱动头文件 - 提供计数获取与硬件初始化接口
 */

#ifndef __ENCODER_H__
#define __ENCODER_H__

/* Includes ------------------------------------------------------------------*/
#include "sys.h"

/* [硬件移植区] --------------------------------------------------------------*/
/* 左侧电机编码器硬件定义 */
#define ENCODER_LEFT_TIM                   TIM2
#define ENCODER_LEFT_TIM_CLK_ENABLE()      __HAL_RCC_TIM2_CLK_ENABLE()
#define ENCODER_LEFT_GPIO_PORT             GPIOA
#define ENCODER_LEFT_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()
#define ENCODER_LEFT_PIN_A                 GPIO_PIN_0
#define ENCODER_LEFT_PIN_B                 GPIO_PIN_1

/* 右侧电机编码器硬件定义 */
#define ENCODER_RIGHT_TIM                  TIM4
#define ENCODER_RIGHT_TIM_CLK_ENABLE()     __HAL_RCC_TIM4_CLK_ENABLE()
#define ENCODER_RIGHT_GPIO_PORT            GPIOB
#define ENCODER_RIGHT_GPIO_CLK_ENABLE()    __HAL_RCC_GPIOB_CLK_ENABLE()
#define ENCODER_RIGHT_PIN_A                GPIO_PIN_7
#define ENCODER_RIGHT_PIN_B                GPIO_PIN_6

/* [配置参数区] --------------------------------------------------------------*/
#define ENCODER_TIM_RELOAD_MAX             ((uint32_t)65535)                    // 16位定时器溢出阈值 (2^16 - 1)
#define ENCODER_INPUT_FILTER_VAL           ((uint8_t)0x0A)                      // 捕获滤波器采样周期阈值 (抗机械抖动)

/* [功能接口声明] ------------------------------------------------------------*/
void    encoder_init(void);                                                     // 统一初始化左右正交编码器硬件
int16_t encoder_left_get_delta(void);                                           // 获取左编码器位置增量并重置基准
int16_t encoder_right_get_delta(void);                                          // 获取右编码器位置增量并重置基准

#endif /* __ENCODER_H__ */
