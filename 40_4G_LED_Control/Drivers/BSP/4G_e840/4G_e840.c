#include "4G_e840.h"
#include "stdio.h"
#include "string.h"
#include "delay.h"
#include "stdarg.h"

// --- 全局变量定义 ---
uint8_t  e840_rx_buf[E840_RX_BUF_SIZE];   // 接收缓冲区，用于存放串口收到的数据
uint8_t  e840_tx_buf[E840_TX_BUF_SIZE];   // 发送缓冲区，用于存放串口要发送的数据
uint16_t e840_cnt = 0;                       // 接收计数器，指示当前写入缓冲区的位置
uint16_t e840_pre_cnt = 0;                   // 上一次计数器值：用于"超时检测"，判断对方是否停止发送

// UART句柄
UART_HandleTypeDef e840_handle = {0};

/**
 * @brief  初始化 e840 连接的串口 (USART2)
 * @param  baudrate: 通信波特率
 */
void e840_uart_init(uint32_t baudrate)
{
    // 1. 配置串口句柄的基本参数
    e840_handle.Instance = USART2;                         //选择外设基地址:USART2
    e840_handle.Init.BaudRate = baudrate;                  //设置波特率
    e840_handle.Init.WordLength = UART_WORDLENGTH_8B;      //子长:8位数据
    e840_handle.Init.StopBits = UART_STOPBITS_1;           //停止位:1位
    e840_handle.Init.Parity = UART_PARITY_NONE;            //检验位:无
    e840_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;      //硬件流控制:无
    e840_handle.Init.Mode = UART_MODE_TX_RX;               //模式:收发模式
    
    // 2. 调用 HAL 库初始化函数
    HAL_UART_Init(&e840_handle);
}



/**
 * @brief  USART2 中断服务函数
 * @note   负责将接收到的单字节存入缓冲区
 */
void USART2_IRQHandler(void)
{
    uint8_t receive_data = 0;
    
    // 检查是否是"接收数据寄存器非空"引起的中断
    if(__HAL_UART_GET_FLAG(&e840_handle, UART_FLAG_RXNE) != RESET)
    {
        // 1. 读取数据
        HAL_UART_Receive(&e840_handle, &receive_data, 1, 1000);
        
        // 2. 将数据存入缓冲区 (防止溢出)
        if(e840_cnt < sizeof(e840_rx_buf))
        {
            e840_rx_buf[e840_cnt++] = receive_data;
        }
        else
        {
            // 缓冲区满，重置索引覆盖旧数据
            e840_cnt = 0;
            e840_rx_buf[e840_cnt++] = receive_data;
        }
    }
}



/**
 * @brief  软件空闲检测 (判断一帧数据是否接收完毕)
 * @note   原理：若一段时间内 cnt 未增加，则认为对方停止发送
 * @return e840_EOK: 接收完毕; e840_EARROR: 接收中或无数据
 */
uint8_t e840_wait_receive(void)
{
    // 情况1: 缓冲区为空，说明根本没数据
    if(e840_cnt == 0)
    {
        return E840_EARROR;
    }
    
    // 情况2: 索引未变化，说明发送结束 (检测到空闲)
    else if(e840_cnt == e840_pre_cnt)
    {
        // 此时认为接收结束，数据包就绪
        if (e840_cnt < E840_RX_BUF_SIZE) 
            {
                e840_rx_buf[e840_cnt] = '\0'; 
            }
        return E840_EOK;        // 返回成功，通知主程序处理数据
    }
    
    // 情况3: 索引还在增加，正在接收中
    else
    { 
        e840_pre_cnt = e840_cnt;      // 同步当前进度
        return E840_EARROR;              // 继续等待
    }
}

/**
 * @brief  清除接收缓冲区
 */
void e840_rx_clar(void)
{
    
    memset(e840_rx_buf, 0, sizeof(e840_rx_buf));  // 清零内存
    e840_cnt = 0;                                    // 重置当前索引
    e840_pre_cnt = 0;                                // 重置历史索引
}




/**
 * @brief  e840 模块初始化流程
 * @note   包含: 存在性检测 -> 设为STA模式 -> 设为单路连接 -> 连接WiFi
 */
void e840_init(uint32_t baudrate)
{
    printf("e840初始化...\r\n");
    e840_uart_init(baudrate);
   
    printf("e840初始化完毕\r\n");
}


/**
 * @brief  主测试逻辑
 * @note   放在 main 的 while(1) 中执行
 */
uint16_t e840_receive_data(char *recv_data)
{
    // 轮询：如果判定一包数据接收完毕
    if(e840_wait_receive() == E840_EOK)
    {
        printf("recv from e840:%s\r\n",e840_rx_buf);     // 打印接收到的字符串
        memcpy(recv_data,e840_rx_buf,strlen((const char *)e840_rx_buf));
        e840_rx_clar();                                     // 清场，为下一包数据做准备
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
void e840_send_data(char *fmt,...)
{
    va_list ap;
    uint16_t len;
    
    // 1. 处理可变参数，格式化字符串到发送缓冲区
    va_start(ap,fmt);
    vsprintf((char *)e840_tx_buf,fmt,ap);
    va_end(ap);
    
    // 2. 通过串口直接发送数据
    len = strlen((const char *)e840_tx_buf);
    HAL_UART_Transmit(&e840_handle,e840_tx_buf,len,100);
}

/**
 * @brief  简单的 AT 测试并打印结果 (调试用)
 */
void e840_test(void)
{
    e840_send_data("TEST:This is from e840\r\n");
//    e840__receive_data();
    
//    // 发送 "AT" 并等待 "OK" 返回
//    if(e840_send_command("AT\r\n","OK") == e840_EOK)
//    {
//        printf("e840_cmd_test%s\r\n",e840_rx_buf);
//    }
}

