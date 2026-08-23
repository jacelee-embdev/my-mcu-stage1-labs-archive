#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "sys.h"

/* ================================================================================= */
/* [硬件移植区] 核心控制引脚与定时器映射配置                                         */
/* ================================================================================= */
/* 电机方向控制引脚 (匹配 L298N/TB6612 等驱动模块逻辑) */
#define MOTOR_DIR_PORT        GPIOB
#define MOTOR_L_BWD_PIN       GPIO_PIN_12    /* 左电机反转控制引脚 */
#define MOTOR_L_FWD_PIN       GPIO_PIN_13    /* 左电机正转控制引脚 */
#define MOTOR_R_BWD_PIN       GPIO_PIN_14    /* 右电机反转控制引脚 */
#define MOTOR_R_FWD_PIN       GPIO_PIN_15    /* 右电机正转控制引脚 */

/* 电机 PWM 调速引脚与定时器配置 (STM32F103C8T6 固定引脚) */
#define MOTOR_PWM_PORT        GPIOA
#define MOTOR_PWM_L_PIN       GPIO_PIN_8     /* 左电机 PWM 输出引脚 (TIM1_CH1) */
#define MOTOR_PWM_R_PIN       GPIO_PIN_11    /* 右电机 PWM 输出引脚 (TIM1_CH4) */
#define MOTOR_PWM_TIM         TIM1           /* 绑定的硬件定时器实例 */

/* 时钟使能宏 */
#define MOTOR_DIR_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()
#define MOTOR_PWM_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()
#define MOTOR_TIM_CLK_ENABLE() __HAL_RCC_TIM1_CLK_ENABLE()

/* ================================================================================= */
/* [配置参数区] 默认软件参数阈值配置                                                 */
/* ================================================================================= */
#define MOTOR_PWM_PERIOD      7199           /* 定时器自动重装载值 (ARR) */
#define MOTOR_PWM_PRESCALER   0              /* 定时器预分频系数 (PSC) */

/* ================================================================================= */
/* [功能接口声明] 外部可调用的应用层 API                                             */
/* ================================================================================= */
void motor_init(void);                                  // 初始化电机方向引脚与 PWM 定时器外设
void motor_left_forward(void);                          // 左电机配置为正转模式
void motor_left_backward(void);                         // 左电机配置为反转模式
void motor_left_stop(void);                             // 左电机触发主动刹车(锁死)
void motor_right_forward(void);                         // 右电机配置为正转模式
void motor_right_backward(void);                        // 右电机配置为反转模式
void motor_right_stop(void);                            // 右电机触发主动刹车(锁死)
void motor_set_speed(int16_t speed_l, int16_t speed_r); // 设置左右电机运行速度与方向
void motor_test_sequence(void);                         // 执行电机全功能逻辑测试序列

#endif /* __MOTOR_H__ */
