#include "uart1.h"
#include "stdio.h"
#include "string.h"

// --- 全局变量定义 ---
uint8_t  uart1_rx_buf[UART1_RX_BUF_SIZE];   // 接收缓冲区，用于存放串口收到的数据
uint16_t uart1_rx_len = 0;                  // 当前接收到的数据长度
uint16_t uart1_cnt = 0;                     // 接收计数器，指示当前写入缓冲区的位置
uint16_t uart1_pre_cnt = 0;                 // 上一次计数器值：用于"超时检测"，判断对方是否停止发送

// UART句柄：HAL库核心结构体，保存串口的所有配置信息态
UART_HandleTypeDef uart1_handle = {0};

/**
 * @brief  初始化串口1
 * @param  baudrate: 波特率
 */
void uart1_init(uint32_t baudrate)
{
    // 1. 配置串口句柄的基本参数
    uart1_handle.Instance = USART1;                         //选择外设基地址:USART1
    uart1_handle.Init.BaudRate = baudrate;                  //设置波特率
    uart1_handle.Init.WordLength = UART_WORDLENGTH_8B;      //子长:8位数据
    uart1_handle.Init.StopBits = UART_STOPBITS_1;           //停止位:1位
    uart1_handle.Init.Parity = UART_PARITY_NONE;            //检验位:无
    uart1_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;      //硬件流控制:无
    uart1_handle.Init.Mode = UART_MODE_TX_RX;               //模式:收发模式
    
    // 2. 调用 HAL 库初始化函数
    HAL_UART_Init(&uart1_handle);
}

/**
 * @brief  硬件底层初始化回调 (MSP)
 * @param  huart: 串口句柄
 */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    //判断是否是串口1,防止影响其它串口初始化
    if(huart->Instance == USART1)
    {
        // 1.开启时钟
        __HAL_RCC_USART1_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        
        // 2.配置GPIO引脚
        GPIO_InitTypeDef gpio_initstruct;
        
        // --- 配置 TX (发送引脚 PA9)
        gpio_initstruct.Pin=GPIO_PIN_9;
        gpio_initstruct.Mode=GPIO_MODE_AF_PP;           // 复用推挽输出
        gpio_initstruct.Pull=GPIO_PULLUP;               // 上拉
        gpio_initstruct.Speed=GPIO_SPEED_FREQ_HIGH;     // 高速
        HAL_GPIO_Init(GPIOA,&gpio_initstruct);
        
        // --- 配置 RX (接收引脚 PA10)
        gpio_initstruct.Pin=GPIO_PIN_10;
        gpio_initstruct.Mode=GPIO_MODE_AF_INPUT;        //复用输入模式
        gpio_initstruct.Pull=GPIO_PULLUP;
        gpio_initstruct.Speed=GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA,&gpio_initstruct);
        
        // 3.配置 NVIC (中断控制器)
        HAL_NVIC_EnableIRQ(USART1_IRQn);            // 使能 USART1 全局中断通道
        HAL_NVIC_SetPriority(USART1_IRQn,2,2);      // 设置中断优先级
        
        // 4.使能串口中断原
        // 使能 RXEN (接收寄存器非空) 中断,当收到数据时触发中断
        __HAL_UART_ENABLE_IT(huart,UART_IT_RXNE);
    }
}

/**
 * @brief  串口1 中断服务函数 (ISR)
 * @note   每收到一个字节，CPU都会暂停主程序跳到这里执行一次
 */
void USART1_IRQHandler(void)
{
    uint8_t receive_data = 0;
    
    // 检查是否是"接收数据寄存器非空"引起的中断
    if(__HAL_UART_GET_FLAG(&uart1_handle, UART_FLAG_RXNE) != RESET)
    {
        // 1. 读取数据
        HAL_UART_Receive(&uart1_handle, &receive_data, 1, 1000);
        
        // 2. 将数据存入缓冲区 (防止溢出)
        if(uart1_cnt < sizeof(uart1_rx_buf))
        {
            uart1_rx_buf[uart1_cnt++] = receive_data;
        }
        else
        {
            // 如果缓冲区满了，重置指针覆盖最早的数据 (循环覆盖策略)
            uart1_cnt = 0;
            uart1_rx_buf[uart1_cnt++] = receive_data;
        }
    }
}

/**
 * @brief  重定向 fputc 函数 (适配 printf)
 * @note   让 printf 的输出内容通过串口1发送出去
 */
int fputc(int ch,FILE *f)
{
    // 1. 等待上一次发送完成
    // 检查状态寄存器(SR)的 TC位 (Transmission Complete)
    // 如果为0，表示忙，死循环等待；如果为1，表示空闲，跳出循环
    while((USART1->SR & 0x40) == 0);

    // 将字符写入数据寄存器 (DR),硬件会自动将其发出
    USART1->DR = (uint8_t)ch;
    
    return ch;
}

/**
 * @brief  软件超时检测 (判断数据包是否接收完毕)
 * @note   需要在主循环中频繁调用
 * @return UART_EOK: 数据包接收完毕; UART_EARROR: 还在接收或无数据
 */
uint8_t uart1_wait_receive(void)
{
    // 情况1: 缓冲区为空，说明根本没数据
    if(uart1_cnt == 0)
    {
        return UART_EARROR;
    }
    
    // 情况2: 核心逻辑 - 比较当前计数器和上次记录的计数器
    // 如果两者相等，说明在两次调用之间，中断没有触发(cnt没增加)
    // 判定为：发送方已经停止发送，一帧数据结束
    else if(uart1_cnt == uart1_pre_cnt)
    {
        // 此时认为接收结束，数据包就绪
        if (uart1_cnt < UART1_RX_BUF_SIZE) {
            uart1_rx_buf[uart1_cnt] = '\0'; 
        }
        return UART_EOK;        // 返回成功，通知主程序处理数据
    }
    
    // 情况3: 收到数据，但计数器还在变大 (正在接收中)
    else
    { 
        // 更新旧值 (同步当前进度)，继续等待下一次检测
        uart1_pre_cnt = uart1_cnt;
        
        // 返回错误状态，表示"还没收完，别急"
        return UART_EARROR;
    }
}

/**
 * @brief  清除接收缓冲区
 */
void uart1_rx_clar(void)
{
    
    memset(uart1_rx_buf, 0, sizeof(uart1_rx_buf));  // 清空缓冲区内存
    uart1_cnt = 0;                                  // 接收计数器归零
    uart1_pre_cnt = 0;
}

/**
 * @brief  主测试逻辑
 * @note   放在 main 的 while(1) 中执行
 */
void uart1__receive_test(void)
{
    // 轮询：如果判定一包数据接收完毕
    if(uart1_wait_receive() == UART_EOK)
    {
        printf("recv:%s\r\n",uart1_rx_buf);     // 打印接收到的字符串
        uart1_rx_clar();                        // 清场，为下一包数据做准备
    }
}

