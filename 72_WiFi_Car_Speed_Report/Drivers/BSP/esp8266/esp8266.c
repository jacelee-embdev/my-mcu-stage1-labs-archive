#include "esp8266.h"
#include "stdio.h"
#include "string.h"
#include "delay.h"
#include "stdarg.h"

// --- 全局变量定义 ---
uint8_t  esp8266_rx_buf[ESP8266_RX_BUF_SIZE];   // 接收缓冲区，用于存放串口收到的数据
uint8_t  esp8266_tx_buf[ESP8266_TX_BUF_SIZE];   // 发送缓冲区，用于存放串口要发送的数据
uint16_t esp8266_cnt = 0;                       // 接收计数器，指示当前写入缓冲区的位置
uint16_t esp8266_pre_cnt = 0;                   // 上一次计数器值：用于"超时检测"，判断对方是否停止发送

// UART句柄
UART_HandleTypeDef esp8266_handle = {0};

/**
 * @brief  初始化 ESP8266 连接的串口 (USART2)
 * @param  baudrate: 通信波特率
 */
void esp8266_uart_init(uint32_t baudrate)
{
    // 1. 配置串口句柄的基本参数
    esp8266_handle.Instance = USART2;                         //选择外设基地址:USART2
    esp8266_handle.Init.BaudRate = baudrate;                  //设置波特率
    esp8266_handle.Init.WordLength = UART_WORDLENGTH_8B;      //子长:8位数据
    esp8266_handle.Init.StopBits = UART_STOPBITS_1;           //停止位:1位
    esp8266_handle.Init.Parity = UART_PARITY_NONE;            //检验位:无
    esp8266_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;      //硬件流控制:无
    esp8266_handle.Init.Mode = UART_MODE_TX_RX;               //模式:收发模式
    
    // 2. 调用 HAL 库初始化函数
    HAL_UART_Init(&esp8266_handle);
}



/**
 * @brief  USART2 中断服务函数
 * @note   负责将接收到的单字节存入缓冲区
 */
void USART2_IRQHandler(void)
{
    uint8_t receive_data = 0;
    
    // 检查是否是"接收数据寄存器非空"引起的中断
    if(__HAL_UART_GET_FLAG(&esp8266_handle, UART_FLAG_RXNE) != RESET)
    {
        // 1. 读取数据
        HAL_UART_Receive(&esp8266_handle, &receive_data, 1, 1000);
        
        // 2. 将数据存入缓冲区 (防止溢出)
        if(esp8266_cnt < sizeof(esp8266_rx_buf))
        {
            esp8266_rx_buf[esp8266_cnt++] = receive_data;
        }
        else
        {
            // 缓冲区满，重置索引覆盖旧数据
            esp8266_cnt = 0;
            esp8266_rx_buf[esp8266_cnt++] = receive_data;
        }
    }
}



/**
 * @brief  软件空闲检测 (判断一帧数据是否接收完毕)
 * @note   原理：若一段时间内 cnt 未增加，则认为对方停止发送
 * @return ESP8266_EOK: 接收完毕; ESP8266_EARROR: 接收中或无数据
 */
uint8_t esp8266_wait_receive(void)
{
    // 情况1: 缓冲区为空，说明根本没数据
    if(esp8266_cnt == 0)
    {
        return ESP8266_EARROR;
    }
    
    // 情况2: 索引未变化，说明发送结束 (检测到空闲)
    else if(esp8266_cnt == esp8266_pre_cnt)
    {
        // 此时认为接收结束，数据包就绪
        if (esp8266_cnt < ESP8266_RX_BUF_SIZE) 
            {
                esp8266_rx_buf[esp8266_cnt] = '\0'; 
            }
        return ESP8266_EOK;        // 返回成功，通知主程序处理数据
    }
    
    // 情况3: 索引还在增加，正在接收中
    else
    { 
        esp8266_pre_cnt = esp8266_cnt;      // 同步当前进度
        return ESP8266_EARROR;              // 继续等待
    }
}

/**
 * @brief  清除接收缓冲区
 */
void esp8266_rx_clar(void)
{
    
    memset(esp8266_rx_buf, 0, sizeof(esp8266_rx_buf));  // 清零内存
    esp8266_cnt = 0;                                    // 重置当前索引
    esp8266_pre_cnt = 0;                                // 重置历史索引
}

/**
 * @brief  向 ESP8266 发送 AT 指令并阻塞等待预期响应
 * @param  cmd:    发送的指令 (例如 "AT\r\n")
 * @param  result: 期待接收到的响应字符串 (例如 "OK")
 * @return ESP8266_EOK: 成功; ESP8266_EARROR: 失败/超时
 */
uint8_t esp8266_send_command(char *cmd,char *result)
{
    uint8_t time_out = 250;     // 超时计数器，250 * 10ms = 2.5秒
    esp8266_rx_clar();
    
    // 发送指令
    HAL_UART_Transmit(&esp8266_handle,(uint8_t *)cmd,strlen(cmd),1000);
    
    // 等待响应
    while(time_out--)
    {
        if(esp8266_wait_receive() == ESP8266_EOK)
        {
            // 在接收缓冲区中查找是否包含期待的 result 字符串
            if(strstr((const char*)esp8266_rx_buf,result) !=NULL)
            {
                return ESP8266_EOK;
            }
        }
        
        delay_ms(10);       // 延时 10ms，避免死循环占用 CPU
    }
    
    return ESP8266_EARROR;
}

/**
 * @brief  AT指令测试 (检查模块是否在线)
 */
uint8_t esp8266_AT_test(void)
{
    return esp8266_send_command("AT\r\n","OK");
}

/**
 * @brief  设置 WiFi 工作模式 (Station/AP)
 * @param  mode: 模式宏定义
 */
uint8_t esp8266_set_mode(uint8_t mode)
{
    switch(mode)
    {
        case ESP8266_STA_MODE:
            return esp8266_send_command("AT+CWMODE=1\r\n","OK");
        case ESP8266_AP_MODE:
            return esp8266_send_command("AT+CWMODE=2\r\n","OK");
        case ESP8266_STA_AR_MODE:
            return esp8266_send_command("AT+CWMODE=3\r\n","OK");
        
        default:
            return ESP8266_EINVAL;
    }
}

/**
 * @brief  设置连接模式 (单路/多路)
 */
uint8_t esp8266_connection_mode(uint8_t mode)
{
    char cmd[64];
    sprintf(cmd,"AT+CIPMUX=%d\r\n",mode);
    return esp8266_send_command(cmd,"OK");
}

/**
 * @brief  连接到指定的 WiFi 热点
 */
uint8_t esp8266_join_ap(char *ssid,char *password)
{
    char cmd[64];
    sprintf(cmd,"AT+CWJAP=\"%s\",\"%s\"\r\n",ssid,password);
    return esp8266_send_command(cmd,"WIFI GOT IP");
}

/**
 * @brief  建立 TCP 连接
 * @param  server_ip:   服务器 IP 地址字符串
 * @param  server_port: 服务器端口号字符串
 * @return ESP8266_EOK: 连接成功; 其它: 失败
 */
uint8_t esp8266_connect_tcp_sever(char *server_ip,char *server_port)
{
    char cmd[64];
    // 拼接 AT 指令: AT+CIPSTART="TCP","IP",PORT
    sprintf(cmd,"AT+CIPSTART=\"TCP\",\"%s\",%s\r\n",server_ip,server_port);
    return esp8266_send_command(cmd,"CONNECT");
}

/**
 * @brief  进入透传模式 (Transparent Transmission)
 * @note   先设置 CIPMODE=1，再发送 CIPSEND 指令
 * 成功后，串口发送的任何数据都会直接转发给服务器
 * @return ESP8266_EOK: 进入成功; ESP8266_EARROR: 失败
 */
uint8_t esp8266_enter_unvannished(void)
{
    uint8_t result;
    // 1. 开启透传模式
    result = esp8266_send_command("AT+CIPMODE=1\r\n","OK");
    
    // 2. 开始发送数据 (等待 ">" 符号)
    // 技巧：利用返回值累加，只要有一步返回非0(错误)，总结果即为非0
    result += esp8266_send_command("AT+CIPSEND\r\n",">");
    
    if(result == ESP8266_EOK)
    {
        return ESP8266_EOK;
    }
    else
    {
        return ESP8266_EARROR;
    }
}

/**
 * @brief  ESP8266 模块初始化流程
 * @note   包含: 存在性检测 -> 设为STA模式 -> 设为单路连接 -> 连接WiFi
 */
void esp8266_init(uint32_t baudrate)
{
    printf("esp8266初始化...\r\n");
    esp8266_uart_init(baudrate);
    
    //esp8266其它初始化
    printf("1.测试esp8266存在性..\r\n");
    while(esp8266_AT_test())
    {
        delay_ms(500);      // 失败则死循环重试
    }
    
    printf("2.设置工作模式为STA...\r\n");
    while(esp8266_set_mode(ESP8266_STA_MODE))
    {
        delay_ms(500);
    }
    
    printf("3.设置单路链接模式...\r\n");
    while(esp8266_connection_mode(ESP8266_SINGLE_CONNECTION))
    {
        delay_ms(500);
    }
    
    printf("4.正在连接至WiFi,SSID:%s,PASSWORD:不告诉你,就是不告诉你,哈哈哈\r\n",WIFI_SSID);
    while(esp8266_join_ap(WIFI_SSID,WIFI_PASSWORD))
    {
        delay_ms(1500);     // 连接WiFi耗时较长，增加延时
    }
    
    printf("5.连接到云服务器,server_ip:%s,server_port:%s ...\r\n",TCP_SERVER_IP,TCP_SERVER_PORT);
    while(esp8266_connect_tcp_sever(TCP_SERVER_IP,TCP_SERVER_PORT))
    {
        delay_ms(500);
    }
    
    printf("6.进入透传模式...\r\n");
    while(esp8266_enter_unvannished())
    {
        delay_ms(500);
    }
    
    // 关键点：初始化结束后，强制清空接收缓冲区
    // 防止最后一条AT指令的响应（回显+OK）被主循环误认为是透传数据
    esp8266_rx_clar();
    
    printf("ESP8266已连接至TCP服务器,并进入透传模式\r\n");
    printf("ESP8266初始化完毕\r\n");
}


/**
 * @brief  主测试逻辑
 * @note   放在 main 的 while(1) 中执行
 */
uint16_t esp8266__receive_data(char *recv_data)
{
    // 轮询：如果判定一包数据接收完毕
    if(esp8266_wait_receive() == ESP8266_EOK)
    {
        printf("recv from esp8266:%s\r\n",esp8266_rx_buf);     // 打印接收到的字符串
        memcpy(recv_data,esp8266_rx_buf,strlen((const char *)esp8266_rx_buf));
        esp8266_rx_clar();                                     // 清场，为下一包数据做准备
        return strlen((const char *)recv_data);
    }
    
    return 0;
}

/**
 * @brief  发送数据 (格式化发送，类似 printf)
 * @note   通常用于透传模式下，直接向服务器发送业务数据
 * @param  fmt: 格式化字符串
 * @param  ...: 可变参数
 */
void esp8266_send_data(char *fmt,...)
{
    va_list ap;
    uint16_t len;
    
    // 1. 处理可变参数，格式化字符串到发送缓冲区
    va_start(ap,fmt);
    vsprintf((char *)esp8266_tx_buf,fmt,ap);
    va_end(ap);
    
    // 2. 通过串口直接发送数据
    len = strlen((const char *)esp8266_tx_buf);
    HAL_UART_Transmit(&esp8266_handle,esp8266_tx_buf,len,100);
}

/**
 * @brief  简单的 AT 测试并打印结果 (调试用)
 */
void esp8266_test(void)
{
    esp8266_send_data("TEST:This is from esp8266\r\n");
//    esp8266__receive_data();
    
//    // 发送 "AT" 并等待 "OK" 返回
//    if(esp8266_send_command("AT\r\n","OK") == ESP8266_EOK)
//    {
//        printf("esp8266_cmd_test%s\r\n",esp8266_rx_buf);
//    }
}

