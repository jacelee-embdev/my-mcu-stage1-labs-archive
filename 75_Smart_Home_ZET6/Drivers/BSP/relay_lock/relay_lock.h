#ifndef __RELAY_LOCK_H__
#define __RELAY_LOCK_H__

#include "sys.h"

/* 硬件移植定义区 */
#define RELAY_LOCK_PORT                GPIOE
#define RELAY_LOCK_PIN                 GPIO_PIN_1
#define RELAY_LOCK_CLK_ENABLE()        __HAL_RCC_GPIOE_CLK_ENABLE()

/* 逻辑电平定义 (低电平触发继电器) */
#define RELAY_LOCK_ON_LEVEL            GPIO_PIN_RESET
#define RELAY_LOCK_OFF_LEVEL           GPIO_PIN_SET

/* 函数声明 */
void relay_lock_init(void);            // 初始化继电器引脚
void relay_lock_on(void);              // 开启继电器（解锁）
void relay_lock_off(void);             // 关闭继电器（上锁）
uint8_t relay_lock_status_get(void);   // 获取当前继电器引脚电平状态
void relay_lock_test(void);            //继电器测试

#endif
