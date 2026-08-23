#ifndef __RELAY_FAN_H__
#define __RELAY_FAN_H__

#include "sys.h"

/* --- 硬件接口定义 --- */
#define RELAY_FAN_GPIO_PORT           GPIOE                           // 端口
#define RELAY_FAN_GPIO_PIN            GPIO_PIN_3                      // 引脚
#define RELAY_FAN_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOE_CLK_ENABLE()    // 时钟使能

/* --- 逻辑状态定义 --- */
#define RELAY_FAN_ON  1
#define RELAY_FAN_OFF 0

/* --- 函数声明 --- */
void relay_fan_init(void);    // 初始化
void relay_fan_on(void);      // 开启
void relay_fan_off(void);     // 关闭
uint8_t relay_fan_status_get(void); // 获取状态
void relay_fan_test(void);   //测试函数
#endif
