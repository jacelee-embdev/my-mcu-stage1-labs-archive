#ifndef __USART_H__
#define __USART_H__

#include "sys.h"

#define UART1_RX_BUF_SIZE   128
#define UART1_TX_BUF_SIZE   128

#define UART_EOK        0
#define UART_EARROR     1
#define UART_ETIMEOUT   2
#define UART_EINVAL     3

void uart1_init(uint32_t baudrate);
void uart1__receive_test(void);

#endif
