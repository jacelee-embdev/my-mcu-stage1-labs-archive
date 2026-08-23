#ifndef __VOICE_H__
#define __VOICE_H__

#include "sys.h"

/* --- 硬件接口定义 --- */
#define VOICE_GPIO_PORT           GPIOF
#define VOICE_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOF_CLK_ENABLE()

// 扩展为 4 位控制（高位到低位：P3, P2, P1, P0）
#define VOICE_PIN3                GPIO_PIN_14   // 新增：最高位 (MSB)
#define VOICE_PIN2                GPIO_PIN_13   
#define VOICE_PIN1                GPIO_PIN_12   
#define VOICE_PIN0                GPIO_PIN_11   // 最低位 (LSB)

/* --- 函数声明 --- */
void voice_init(void);          // 初始化 (开启中断)
uint8_t voice_get_cmd(void);    // 获取指令并复位

#endif
