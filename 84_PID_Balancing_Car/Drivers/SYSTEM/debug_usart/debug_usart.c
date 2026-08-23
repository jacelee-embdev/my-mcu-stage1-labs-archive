#include "debug_usart.h"
#include "string.h"

UART_HandleTypeDef debug_usart_handle;
uint8_t debug_usart_rx_buf[DEBUG_USART_RX_BUF_SIZE];
uint16_t debug_usart_rx_len = 0;

// 重定向printf
int fputc(int ch, FILE *f)
{
    while ((DEBUG_USART->SR & 0X40) == 0);
    DEBUG_USART->DR = (uint8_t)ch;
    return ch;
}

// 串口初始化
void debug_usart_init(uint32_t baudrate)
{
    debug_usart_handle.Instance = DEBUG_USART;
    debug_usart_handle.Init.BaudRate = baudrate;
    debug_usart_handle.Init.WordLength = UART_WORDLENGTH_8B;
    debug_usart_handle.Init.StopBits = UART_STOPBITS_1;
    debug_usart_handle.Init.Parity = UART_PARITY_NONE;
    debug_usart_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    debug_usart_handle.Init.Mode = UART_MODE_TX_RX;
    
    HAL_UART_Init(&debug_usart_handle);
}

// 底层硬件初始化
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef gpio_init_struct;

    if (huart->Instance == DEBUG_USART)
    {
        // 开启时钟
        DEBUG_USART_TX_CLK_ENABLE();
        DEBUG_USART_RX_CLK_ENABLE();
        DEBUG_USART_CLK_ENABLE();

        // 配置TX引脚
        gpio_init_struct.Pin = DEBUG_USART_TX_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(DEBUG_USART_TX_PORT, &gpio_init_struct);
                
        // 配置RX引脚
        gpio_init_struct.Pin = DEBUG_USART_RX_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_INPUT;
        HAL_GPIO_Init(DEBUG_USART_RX_PORT, &gpio_init_struct);
        
        // 中断配置
        HAL_NVIC_EnableIRQ(DEBUG_USART_IRQn);
        HAL_NVIC_SetPriority(DEBUG_USART_IRQn, 3, 3);

        // 开启中断位
        __HAL_UART_ENABLE_IT(huart, UART_IT_RXNE);
        __HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);
    }
    // 判断是否为 USART3
    else if(huart->Instance == USART3)
    {
        /* 1. 使能时钟 */
        __HAL_RCC_USART3_CLK_ENABLE();          // 使能外设时钟
        USART3_TX_CLK_ENABLE();                 // 使能 TX 端口时钟
        USART3_RX_CLK_ENABLE();                 // 使能 RX 端口时钟
        
        /* 2. 配置 TX 引脚 (复用推挽) */
        gpio_init_struct.Pin   = USART3_TX_PIN;
        gpio_init_struct.Mode  = GPIO_MODE_AF_PP;           
        gpio_init_struct.Pull  = GPIO_PULLUP;               
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;     
        HAL_GPIO_Init(USART3_TX_PORT, &gpio_init_struct);
        
        /* 3. 配置 RX 引脚 (复用输入) */
        gpio_init_struct.Pin   = USART3_RX_PIN;
        gpio_init_struct.Mode  = GPIO_MODE_AF_INPUT;        
        HAL_GPIO_Init(USART3_RX_PORT, &gpio_init_struct);
        
        /* 4. 配置 NVIC */
        HAL_NVIC_EnableIRQ(USART3_IRQn);            
        HAL_NVIC_SetPriority(USART3_IRQn, 3, 3);      
        
        /* 5. 使能中断源 */
        __HAL_UART_ENABLE_IT(huart, UART_IT_RXNE);  // 接收中断
        __HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);  // 空闲中断
    }
}

// 清空接收缓冲区
void debug_usart_rx_clear(void)
{
    memset(debug_usart_rx_buf, 0, sizeof(debug_usart_rx_buf));
    debug_usart_rx_len = 0;
}

// 中断服务函数
void DEBUG_USART_IRQHandler(void)
{
    uint8_t receive_data = 0;   
    
    // 接收中断处理
    if(__HAL_UART_GET_FLAG(&debug_usart_handle, UART_FLAG_RXNE) != RESET)
    {
        if(debug_usart_rx_len >= sizeof(debug_usart_rx_buf))
            debug_usart_rx_len = 0;
            
        HAL_UART_Receive(&debug_usart_handle, &receive_data, 1, 1000);
        debug_usart_rx_buf[debug_usart_rx_len++] = receive_data;
    }

    // 空闲中断处理
    if (__HAL_UART_GET_FLAG(&debug_usart_handle, UART_FLAG_IDLE) != RESET)
    {
        printf("recv: %s\r\n", debug_usart_rx_buf);
        debug_usart_rx_clear();
        __HAL_UART_CLEAR_IDLEFLAG(&debug_usart_handle);
    }
}
