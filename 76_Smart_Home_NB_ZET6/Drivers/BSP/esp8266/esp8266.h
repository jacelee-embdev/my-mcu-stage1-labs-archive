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
#define WIFI_SSID                   "XXXX"
#define WIFI_PASSWORD               "XXXX"

/* 云服务器 信息 */
#define TCP_SERVER_IP                "mqtts.heclouds.com"
#define TCP_SERVER_PORT              "1883"

void esp8266_init(uint32_t baudrate);
uint8_t esp8266_wait_receive(void);
void esp8266_send_data(char *data,uint16_t len);
uint16_t esp8266_copy_rxdata(char *data);

#endif
