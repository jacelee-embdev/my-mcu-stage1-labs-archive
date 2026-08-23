#include "usart1.h"
#include "string.h"

/* 串口句柄 */
UART_HandleTypeDef usart1_handle;

/* 接收缓冲区 */
uint8_t usart1_rx_buf[USART1_RX_BUF_SIZE];
uint16_t usart1_rx_len = 0;

/**
 * @brief       重定义fputc (供printf使用)
 */
int fputc(int ch, FILE *f)
{
    while ((USART1->SR & 0X40) == 0);       /* 等待发送完成 */
    USART1->DR = (uint8_t)ch;               /* 发送数据 */
    return ch;
}

/**
 * @brief       串口初始化
 */
void usart1_init(uint32_t baudrate)
{
    usart1_handle.Instance = USART1;                        /* 直接指定 USART1 */
    usart1_handle.Init.BaudRate = baudrate;
    usart1_handle.Init.WordLength = UART_WORDLENGTH_8B;
    usart1_handle.Init.StopBits = UART_STOPBITS_1;
    usart1_handle.Init.Parity = UART_PARITY_NONE;
    usart1_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    usart1_handle.Init.Mode = UART_MODE_TX_RX;
    
    HAL_UART_Init(&usart1_handle);
}

/**
 * @brief       HAL库底层初始化回调
 */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef gpio_init_struct;

    if (huart->Instance == USART1)
    {
        /* 1. 使能时钟 */
        USART1_TX_CLK_ENABLE();                 /* 使能TX GPIO时钟 (宏定义) */
        USART1_RX_CLK_ENABLE();                 /* 使能RX GPIO时钟 (宏定义) */
        __HAL_RCC_USART1_CLK_ENABLE();          /* 使能USART1时钟 */

        /* 2. 配置TX引脚 */
        gpio_init_struct.Pin = USART1_TX_PIN;   /* 使用宏定义 */
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(USART1_TX_PORT, &gpio_init_struct);
                
        /* 3. 配置RX引脚 */
        gpio_init_struct.Pin = USART1_RX_PIN;   /* 使用宏定义 */
        gpio_init_struct.Mode = GPIO_MODE_AF_INPUT;
        HAL_GPIO_Init(USART1_RX_PORT, &gpio_init_struct);
        
        /* 4. 配置中断 */
        HAL_NVIC_EnableIRQ(USART1_IRQn);
        HAL_NVIC_SetPriority(USART1_IRQn, 3, 3);

        /* 5. 开启接收和空闲中断 */
        __HAL_UART_ENABLE_IT(huart, UART_IT_RXNE);
        __HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);
    }

    // 判断是否为 USART2
    else if(huart->Instance == USART2)
    {
        /* 1. 使能时钟 */
        __HAL_RCC_USART2_CLK_ENABLE();          // 使能外设时钟
        USART2_TX_CLK_ENABLE();                 // 使能 TX 端口时钟
        USART2_RX_CLK_ENABLE();                 // 使能 RX 端口时钟
        
        /* 2. 配置 TX 引脚 (复用推挽) */
        gpio_init_struct.Pin   = USART2_TX_PIN;
        gpio_init_struct.Mode  = GPIO_MODE_AF_PP;           
        gpio_init_struct.Pull  = GPIO_PULLUP;               
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;     
        HAL_GPIO_Init(USART2_TX_PORT, &gpio_init_struct);
        
        /* 3. 配置 RX 引脚 (复用输入) */
        gpio_init_struct.Pin   = USART2_RX_PIN;
        gpio_init_struct.Mode  = GPIO_MODE_AF_INPUT;        
        HAL_GPIO_Init(USART2_RX_PORT, &gpio_init_struct);
        
        /* 4. 配置 NVIC */
        HAL_NVIC_EnableIRQ(USART2_IRQn);            
        HAL_NVIC_SetPriority(USART2_IRQn, 3, 3);      
        
        /* 5. 使能中断源 */
        __HAL_UART_ENABLE_IT(huart, UART_IT_RXNE);  // 接收中断
        __HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);  // 空闲中断
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
//        __HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);  // 空闲中断
    }
}

/**
 * @brief       清空缓冲区
 */
void usart1_rx_clear(void)
{
    memset(usart1_rx_buf, 0, sizeof(usart1_rx_buf));
    usart1_rx_len = 0;
}

/**
 * @brief       串口中断服务函数
 */
void USART1_IRQHandler(void)
{
    uint8_t receive_data = 0;   
    
    /* 接收数据中断 */
    if(__HAL_UART_GET_FLAG(&usart1_handle, UART_FLAG_RXNE) != RESET){
        if(usart1_rx_len >= sizeof(usart1_rx_buf))
            usart1_rx_len = 0;
            
        HAL_UART_Receive(&usart1_handle, &receive_data, 1, 1000);
        usart1_rx_buf[usart1_rx_len++] = receive_data;
    }

    /* 空闲中断 (一帧数据接收完毕) */
    if (__HAL_UART_GET_FLAG(&usart1_handle, UART_FLAG_IDLE) != RESET)
    {
        printf("recv: %s\r\n", usart1_rx_buf);
        usart1_rx_clear();
        __HAL_UART_CLEAR_IDLEFLAG(&usart1_handle);
    }
}
