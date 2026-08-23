#include "uart1.h"
#include "stdio.h"
#include "string.h"

// --- 全局变量定义 ---
uint8_t  uart1_rx_buf[UART1_RX_BUF_SIZE];   // 接收缓冲区，用于存放串口收到的数据
uint16_t uart1_rx_len = 0;                  // 当前接收到的数据长度

// UART句柄：HAL库核心结构体，保存串口配置
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
        
        // 开启 IDLE (空闲) 中断：用于判断一包数据结束
        __HAL_UART_ENABLE_IT(huart,UART_IT_IDLE);
    }
}

/**
 * @brief  清除接收缓冲区
 */
void uart1_rx_clar(void)
{
    memset(uart1_rx_buf, 0, sizeof(uart1_rx_buf));  // 清空缓冲区内存
    uart1_rx_len = 0;                               // 重置数据长度
}

/**
 * @brief  串口1 中断服务函数
 * @note   处理数据接收和空闲检测
 */
void USART1_IRQHandler(void)
{
    uint8_t receive_data = 0;
    
    // --- 1. 处理 RXNE 中断 (收到数据) ---
    if(__HAL_UART_GET_FLAG(&uart1_handle, UART_FLAG_RXNE) != RESET)
    {
        // 读取一个字节 (读取操作会自动清除 RXNE 标志)
        HAL_UART_Receive(&uart1_handle, &receive_data, 1, 1000);
        
        // 将数据存入缓冲区 (含溢出保护)
        if(uart1_rx_len < sizeof(uart1_rx_buf))
        {
            uart1_rx_buf[uart1_rx_len++] = receive_data;
        }
        else
        {
            // 缓冲区满，覆盖最早的数据
            uart1_rx_len = 0;
            uart1_rx_buf[uart1_rx_len++] = receive_data;
        }
    }
    
    // --- 2. 处理 IDLE 中断 (数据包结束) ---
    if(__HAL_UART_GET_FLAG(&uart1_handle, UART_FLAG_IDLE) != RESET)
    {
        printf("recv:%s\r\n",uart1_rx_buf);         // 打印接收到的数据
        uart1_rx_clar();                            // 清空缓冲区，为下次接收做准备
        __HAL_UART_CLEAR_IDLEFLAG(&uart1_handle);   // 清除 IDLE 标志位 (防止重复进入中断)
    }
}

/**
 * @brief  重定向 fputc (供 printf 使用)
 */
int fputc(int ch,FILE *f)
{
    // 等待上一次发送完成 (TC=1)
    while((USART1->SR & 0x40) == 0);

    // 写入数据寄存器发送
    USART1->DR = (uint8_t)ch;
    
    return ch;
}





