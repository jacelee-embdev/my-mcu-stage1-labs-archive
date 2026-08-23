#include "dma.h"
#include "sys.h"
#include "stdio.h"

#define BUF_SIZE    16      // 定义缓冲区大小为 16 个字（32位）

/* 源数据缓冲区：待传输的原始数据 */
uint32_t src_buf[BUF_SIZE] = {
    0x00000000,0x11111111,0x22222222,0x33333333,
    0x44444444,0x55555555,0x66666666,0x77777777,
    0x88888888,0x99999999,0xAAAAAAAA,0xBBBBBBBB,
    0xCCCCCCCC,0xDDDDDDDD,0xEEEEEEEE,0xFFFFFFFF
};

uint32_t dst_buf[BUF_SIZE] = {0};       /* 目标数据缓冲区：用于接收 DMA 传输的数据 */

/* DMA 句柄结构体：用于配置 DMA 参数 */
DMA_HandleTypeDef dma_handle = {0};

/**
 * @brief DMA 初始化函数
 */
void dam_init(void)
{
    __HAL_RCC_DMA1_CLK_ENABLE();                                    // 使能 DMA1 时钟
    dma_handle.Instance = DMA1_Channel1;                            // 使用 DMA1 的通道 1
    dma_handle.Init.Direction = DMA_MEMORY_TO_MEMORY;               // 传输方向：内存到内存
    
    // 目标地址（在 M2M 模式下被视为存储器）配置
    dma_handle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;         // 目标数据对齐：字节
    dma_handle.Init.MemInc = DMA_MINC_ENABLE;                       // 目标地址自增
    
    // 源地址（在 M2M 模式下被视为外设）配置
    dma_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;      // 源数据对齐：字节
    dma_handle.Init.PeriphInc = DMA_PINC_ENABLE;                    // 源地址自增
    
    dma_handle.Init.Priority = DMA_PRIORITY_MEDIUM;                 // 传输优先级：中等
    dma_handle.Init.Mode = DMA_NORMAL;                              // 普通模式（传输一次即停止，不循环）
    HAL_DMA_Init(&dma_handle);                                      // 根据上述配置初始化 DMA
}

/**
 * @brief 执行 DMA 传输并打印结果
 */
void dma_transmit(void)
{
    /* 开启 DMA 传输：指定源地址、目的地址和数据长度 */
    HAL_DMA_Start(&dma_handle,(uint32_t)src_buf,(uint32_t)dst_buf,sizeof(uint32_t) * BUF_SIZE);
    
    /* 等待传输完成标志位（TC - Transfer Complete）置位 */
    while(__HAL_DMA_GET_FLAG(&dma_handle,DMA_FLAG_TC1)  == RESET);
    
    /* 传输完成后，通过串口打印目标缓冲区的数据，验证是否传输成功 */
    int i = 0;
    for(i=0;i<BUF_SIZE;i++)
    {
        printf("buf[%d] = %X\r\n",i,dst_buf[i]);
    }
}
