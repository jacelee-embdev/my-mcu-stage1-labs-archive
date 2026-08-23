#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include "sys.h"

/*------------------------------------------------------------------------------
 * 硬件移植区
 * 注意:除了此处,还需修改 "keyboard.c" 里的中断线
 *----------------------------------------------------------------------------*/

// 端口与时钟定义
#define KBD_PORT                GPIOF
#define KBD_PORT_CLK_ENABLE()   __HAL_RCC_GPIOF_CLK_ENABLE()

// 行引脚定义 (Row: 输入/中断)
#define KBD_ROW1_PIN            GPIO_PIN_0
#define KBD_ROW2_PIN            GPIO_PIN_1
#define KBD_ROW3_PIN            GPIO_PIN_2
#define KBD_ROW4_PIN            GPIO_PIN_3

// 列引脚定义 (Column: 扫描输出)
#define KBD_COL1_PIN            GPIO_PIN_4
#define KBD_COL2_PIN            GPIO_PIN_5
#define KBD_COL3_PIN            GPIO_PIN_6
#define KBD_COL4_PIN            GPIO_PIN_7

/*------------------------------------------------------------------------------
 * 函数声明 (Function Prototypes)
 *----------------------------------------------------------------------------*/

void keyboard_init(void);           //初始化矩阵键盘 GPIO
uint8_t keyboard_get_value(void);   //获取当前按下的按键键值
void keboard_test(void);         //键盘功能测试函数

#endif
