#ifndef __USART1_H__
#define __USART1_H__

#include "sys.h"
#include "stdio.h"

/* --- USART1 硬件配置 --- */
#define USART1_TX_PORT              GPIOA                           // TX 端口
#define USART1_TX_PIN               GPIO_PIN_9                      // TX 引脚
#define USART1_TX_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()    // TX 端口时钟

#define USART1_RX_PORT              GPIOA                           // RX 端口
#define USART1_RX_PIN               GPIO_PIN_10                     // RX 引脚
#define USART1_RX_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()    // RX 端口时钟

/* --- USART2 硬件配置 --- */
#define USART2_TX_PORT              GPIOA                           // TX 端口
#define USART2_TX_PIN               GPIO_PIN_2                      // TX 引脚
#define USART2_TX_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()    // TX 端口时钟

#define USART2_RX_PORT              GPIOA                           // RX 端口
#define USART2_RX_PIN               GPIO_PIN_3                      // RX 引脚
#define USART2_RX_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()    // RX 端口时钟

/* --- USART3 硬件配置 --- */
#define USART3_TX_PORT              GPIOB                           // TX 端口
#define USART3_TX_PIN               GPIO_PIN_10                      // TX 引脚
#define USART3_TX_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()    // TX 端口时钟

#define USART3_RX_PORT              GPIOB                           // RX 端口
#define USART3_RX_PIN               GPIO_PIN_11                      // RX 引脚
#define USART3_RX_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()    // RX 端口时钟

/* --- 公共配置 --- */
#define USART1_RX_BUF_SIZE          128

void usart1_init(uint32_t baudrate);
void usart1_rx_clear(void);

#endif
