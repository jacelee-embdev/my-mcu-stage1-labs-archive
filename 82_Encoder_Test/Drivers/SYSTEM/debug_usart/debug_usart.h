#ifndef __DEBUG_USART_H__
#define __DEBUG_USART_H__

#include "sys.h"
#include "stdio.h"

// 硬件配置宏定义
#define DEBUG_USART                     USART2
#define DEBUG_USART_CLK_ENABLE()        __HAL_RCC_USART2_CLK_ENABLE()
#define DEBUG_USART_IRQn                USART2_IRQn
#define DEBUG_USART_IRQHandler          USART2_IRQHandler

// TX引脚配置 (PA2)
#define DEBUG_USART_TX_PORT             GPIOA
#define DEBUG_USART_TX_PIN              GPIO_PIN_2
#define DEBUG_USART_TX_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()

// RX引脚配置 (PA3)
#define DEBUG_USART_RX_PORT             GPIOA
#define DEBUG_USART_RX_PIN              GPIO_PIN_3
#define DEBUG_USART_RX_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()

// 缓冲区大小
#define DEBUG_USART_RX_BUF_SIZE         128

// 函数声明
void debug_usart_init(uint32_t baudrate);
void debug_usart_rx_clear(void);

#endif
