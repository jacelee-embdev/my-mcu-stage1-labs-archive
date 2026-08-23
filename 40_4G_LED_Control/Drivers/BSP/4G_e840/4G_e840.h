#ifndef __4G_E840_H__
#define __4G_E840_H__

#include "sys.h"

/* 缓冲区大小定义 */
#define E840_RX_BUF_SIZE         128     // 接收缓冲区大小
#define E840_TX_BUF_SIZE         128     // 发送缓冲区大小

/* 返回状态定义 */
#define E840_EOK                 0       // 操作成功
#define E840_EARROR              1       // 操作失败/错误
#define E840_ETIMEOUT            2       // 超时
#define E840_EINVAL              3       // 参数无效



void e840_init(uint32_t baudrate);
void e840_test(void);
uint16_t e840_receive_data(char *recv_data);

#endif
