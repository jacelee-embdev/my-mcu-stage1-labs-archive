#include "dma.h"
#include "sys.h"
#include "stdio.h"
#include "uart1.h"

/* 声明外部定义的串口句柄，以便进行 DMA 关联 */
extern UART_HandleTypeDef uart1_handle;

/* DMA 句柄结构体：用于配置 DMA 参数 */
DMA_HandleTypeDef dma_handle = {0};

/**
 * @brief DMA 初始化函数
 * @note  配置 DMA1 通道 4 用于 USART1_TX 的数据传输
 */
void dam_init(void)
{
    /* 1. 使能 DMA1 时钟 */
    __HAL_RCC_DMA1_CLK_ENABLE();
    
    /* 2. 配置 DMA 传输实例：STM32F103 的 USART1_TX 固定连接在 DMA1 通道 4 */
    dma_handle.Instance = DMA1_Channel4;
    
    /* 3. 设置传输方向：从内存到外设（串口发送数据） */
    dma_handle.Init.Direction = DMA_MEMORY_TO_PERIPH;
    
    /* 4. 存储器（内存）配置 */
    dma_handle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;         /* 内存数据宽度：8位（字节） */
    dma_handle.Init.MemInc = DMA_MINC_ENABLE;                       /* 内存地址自增：每发送一个字节地址自动移动到下一个字节 */
    
    /* 5. 外设（串口）配置 */
    dma_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;      /* 外设数据宽度：8位（字节） */
    dma_handle.Init.PeriphInc = DMA_PINC_DISABLE;                   /* 外设地址不自增：始终指向串口的数据寄存器（DR） */
    
    /* 6. 传输模式与优先级配置 */
    dma_handle.Init.Priority = DMA_PRIORITY_MEDIUM;                 /* 优先级：中等 */
    dma_handle.Init.Mode = DMA_NORMAL;                              /* 普通模式：传输指定长度后自动停止，不循环 */
    
    /* 7. 执行 DMA 初始化 */
    HAL_DMA_Init(&dma_handle);
    
    /* 8. 关联句柄：将 DMA 句柄与串口句柄的发送 DMA 指针（hdmatx）链接起来 */
    __HAL_LINKDMA(&uart1_handle,hdmatx,dma_handle);
}

