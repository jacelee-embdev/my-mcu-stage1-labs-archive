#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

#include "sys.h"

/* ================================================================================= */
/* [配置参数区] 缓冲区大小与状态宏定义                                                 */
/* ================================================================================= */
#define UART3_RX_BUF_SIZE   128
#define UART3_TX_BUF_SIZE   128

#define UART_EOK        0
#define UART_EARROR     1
#define UART_ETIMEOUT   2
#define UART_EINVAL     3

/* ================================================================================= */
/* [功能接口声明] 蓝牙对外开放 API                                                     */
/* ================================================================================= */
void bluetooth_init(uint32_t baudrate);                 // 初始化串口3配置
void uart3_rx_clear(void);                              // 清除串口3接收缓冲区
void bluetooth_send(char * format,...);                 // 格式化发送数据到蓝牙(串口3)
uint8_t bluetooth_get_command(void);                    // 获取蓝牙接收到的单字节指令

#endif
