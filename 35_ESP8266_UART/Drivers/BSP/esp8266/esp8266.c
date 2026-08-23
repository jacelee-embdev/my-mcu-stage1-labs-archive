#include "esp8266.h"
#include "stdio.h"
#include "string.h"
#include "delay.h"

// --- 全局变量定义 ---
uint8_t  esp8266_rx_buf[ESP8266_RX_BUF_SIZE];   // 接收缓冲区，用于存放串口收到的数据
uint16_t esp8266_cnt = 0;                     // 接收计数器，指示当前写入缓冲区的位置
uint16_t esp8266_pre_cnt = 0;                 // 上一次计数器值：用于"超时检测"，判断对方是否停止发送

// UART句柄：HAL库核心结构体，保存串口的所有配置信息态
UART_HandleTypeDef esp8266_handle = {0};

/**
 * @brief  初始化 ESP8266 连接的串口 (USART2)
 * @note   注意：代码中使用的是 USART2，请确保硬件接线正确
 * @param  baudrate: 波特率
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
 * @brief  USART2 中断服务函数 (ISR)
 * @note   每收到一个字节，CPU都会暂停主程序跳到这里执行一次
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
            // 如果缓冲区满了，重置指针覆盖最早的数据 (循环覆盖策略)
            esp8266_cnt = 0;
            esp8266_rx_buf[esp8266_cnt++] = receive_data;
        }
    }
}



/**
 * @brief  软件超时检测 (判断数据包是否接收完毕)
 * @note   需要在主循环中频繁调用
 * @return UART_EOK: 数据包接收完毕; UART_EARROR: 还在接收或无数据
 */
uint8_t esp8266_wait_receive(void)
{
    // 情况1: 缓冲区为空，说明根本没数据
    if(esp8266_cnt == 0)
    {
        return ESP8266_EARROR;
    }
    
    // 情况2: 核心逻辑 - 比较当前计数器和上次记录的计数器
    // 如果两者相等，说明在两次调用之间，中断没有触发(cnt没增加)
    // 判定为：发送方已经停止发送，一帧数据结束
    else if(esp8266_cnt == esp8266_pre_cnt)
    {
        // 此时认为接收结束，数据包就绪
        if (esp8266_cnt < ESP8266_RX_BUF_SIZE) 
            {
                esp8266_rx_buf[esp8266_cnt] = '\0'; 
            }
        return ESP8266_EOK;        // 返回成功，通知主程序处理数据
    }
    
    // 情况3: 收到数据，但计数器还在变大 (正在接收中)
    else
    { 
        // 更新旧值 (同步当前进度)，继续等待下一次检测
        esp8266_pre_cnt = esp8266_cnt;
        
        // 返回错误状态，表示"还没收完，别急"
        return ESP8266_EARROR;
    }
}

/**
 * @brief  清除接收缓冲区
 */
void esp8266_rx_clar(void)
{
    
    memset(esp8266_rx_buf, 0, sizeof(esp8266_rx_buf));  // 清空缓冲区内存
    esp8266_cnt = 0;                                  // 接收计数器归零
    esp8266_pre_cnt = 0;
}

/**
 * @brief  主测试逻辑
 * @note   放在 main 的 while(1) 中执行
 */
void esp8266__receive_data(void)
{
    // 轮询：如果判定一包数据接收完毕
    if(esp8266_wait_receive() == ESP8266_EOK)
    {
        printf("recv from esp8266:%s\r\n",esp8266_rx_buf);     // 打印接收到的字符串
        esp8266_rx_clar();                        // 清场，为下一包数据做准备
    }
}


/**
 * @brief  ESP8266 模块总初始化函数
 * @param  baudrate: 通信波特率
 */
void esp8266_init(uint32_t baudrate)
{
    esp8266_uart_init(baudrate);
    
    //esp8266其它初始化
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
    
    // 通过 USART2 发送指令
    HAL_UART_Transmit(&esp8266_handle,(uint8_t *)cmd,strlen(cmd),1000);
    
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
 * @brief  ESP8266 测试函数
 * @note   发送 AT 指令测试模块是否在线
 */
void esp8266_test(void)
{
    // 发送 "AT" 并等待 "OK" 返回
    if(esp8266_send_command("AT\r\n","OK") == ESP8266_EOK)
    {
        printf("esp8266_cmd_test%s\r\n",esp8266_rx_buf);
    }
}

