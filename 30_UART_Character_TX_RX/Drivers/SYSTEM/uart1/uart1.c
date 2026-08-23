#include "uart1.h"

//定义串口1的句柄结构体,用于保存串口的配置信息和状态
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
    // 该函数会应用上述配置，并自动调用 HAL_UART_MspInit 进行底层硬件初始化
    HAL_UART_Init(&uart1_handle);
}

/**
 * @brief  串口底层硬件初始化回调函数 (MSP: MCU Support Package)
 * 此函数会被 HAL_UART_Init() 自动调用
 * @param  huart: 串口句柄指针
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
 * @brief  USART1 中断服务函数 (ISR)
 * 当发生串口中断时，CPU 会跳转到这里执行
 */
void USART1_IRQHandler(void)
{
    uint8_t receive_data = 0;
    
    // 检查是否是 RXNE (接收数据寄存器非空) 标志位被置位
    // 这一步确认中断是由"接收数据"引起的
    if(__HAL_UART_GET_FLAG(&uart1_handle,UART_FLAG_RXNE) != RESET)
    {
        // 1.读取接收到的 1 个字节数据
        //读取操作会自动清楚 RXEN 标志位
        HAL_UART_Receive(&uart1_handle,&receive_data,1,1000);
        
        // 2.将收到的数据原样发送回去 (Echo)
        HAL_UART_Transmit(&uart1_handle,&receive_data,1,1000);
    }
}
