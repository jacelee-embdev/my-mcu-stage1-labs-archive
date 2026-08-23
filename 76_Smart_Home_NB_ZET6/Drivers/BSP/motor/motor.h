#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "sys.h" 

/* ==========================================================
 * 硬件引脚配置宏定义
 * ========================================================== */

/* --- PWM 定时器配置 (TIM8) --- */
#define MOTOR_TIM_HANDLE           htim8
#define MOTOR_TIM_INSTANCE         TIM8
#define MOTOR_TIM_CLK_ENABLE()     __HAL_RCC_TIM8_CLK_ENABLE()

/* --- 锁控电机 (Lock Motor) 硬件定义 --- */
// PWM (ENA) -> PC7 (TIM8_CH2)
#define LOCK_PWM_PORT              GPIOC
#define LOCK_PWM_PIN               GPIO_PIN_7
#define LOCK_PWM_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE()
#define LOCK_PWM_CHANNEL           TIM_CHANNEL_2

// 方向控制 (IN1/IN2) -> PB8, PB9
#define LOCK_DIR_PORT              GPIOB
#define LOCK_IN1_PIN               GPIO_PIN_4
#define LOCK_IN2_PIN               GPIO_PIN_5
#define LOCK_DIR_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()

/* --- 风扇电机 (Fan Motor) 硬件定义 --- */
// PWM (ENB) -> PC8 (TIM8_CH3)
#define FAN_PWM_PORT               GPIOC
#define FAN_PWM_PIN                GPIO_PIN_8
#define FAN_PWM_CLK_ENABLE()       __HAL_RCC_GPIOC_CLK_ENABLE()
#define FAN_PWM_CHANNEL            TIM_CHANNEL_3

// 方向控制 (IN3/IN4) -> PB6, PB7
#define FAN_DIR_PORT               GPIOB
#define FAN_IN3_PIN                GPIO_PIN_6
#define FAN_IN4_PIN                GPIO_PIN_7
#define FAN_DIR_CLK_ENABLE()       __HAL_RCC_GPIOB_CLK_ENABLE()

/* ==========================================================
 * 数据类型与函数声明
 * ========================================================== */

// 电机状态枚举
typedef enum {
    MOTOR_STOP = 0,   // 停止
    MOTOR_FWD,        // 正转
    MOTOR_REV         // 反转
} motor_state_t;

// 模块初始化
void motor_init(void);

// 锁控电机控制 API
void lock_motor_set(motor_state_t state, uint16_t speed);
void lock_motor_stop(void);

// 风扇电机控制 API
void fan_motor_set(motor_state_t state, uint16_t speed);
void fan_motor_stop(void);

/* --- 应用层控制接口 --- */
void door_open(void);    // 开门函数：正转 10s 后停止
void door_close(void);   // 关门函数：反转 10s 后停止
void fan_run_80pct(void); // 风扇函数：40% 占空比持续正转

void motor_total_test(void);


#endif /* __MOTOR_H__ */
