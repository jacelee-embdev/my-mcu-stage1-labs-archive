#ifndef __ESP8266_H__
#define __ESP8266_H__

#include "sys.h"

/* 缓冲区大小定义 */
#define ESP8266_RX_BUF_SIZE         128     // 接收缓冲区大小
#define ESP8266_TX_BUF_SIZE         128     // 发送缓冲区大小

/* 返回状态定义 */
#define ESP8266_EOK                 0       // 操作成功
#define ESP8266_EARROR              1       // 操作失败/错误
#define ESP8266_ETIMEOUT            2       // 超时
#define ESP8266_EINVAL              3       // 参数无效

/* WIFI 工作模式 (AT+CWMODE) */
#define ESP8266_STA_MODE            1       // Station 模式 (客户端)
#define ESP8266_AP_MODE             2       // AP 模式 (热点)
#define ESP8266_STA_AR_MODE         3       // STA + AP 混合模式

/* 连接模式 (AT+CIPMUX) */
#define ESP8266_SINGLE_CONNECTION   0       // 单路连接模式
#define ESP8266_MULTI_CONNECTION    1       // 多路连接模式

/* WiFi 账户信息 */
#define WIFI_SSID                   "XXXXX"
#define WIFI_PASSWORD               "XXXXX"

/* 云服务器 信息 */
#define TCP_SERVER_IP                "XXX.XXX.XXX.XXX"
#define TCP_SERVER_PORT              "8080"

void esp8266_init(uint32_t baudrate);
void esp8266_test(void);
uint16_t esp8266__receive_data(char *recv_data);
void esp8266_send_data(char *fmt,...);

#endif
