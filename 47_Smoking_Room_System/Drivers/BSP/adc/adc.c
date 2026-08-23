#include "adc.h"
#include "sys.h"



// 定义 ADC 句柄，用于管理 ADC1 的状态
ADC_HandleTypeDef adc_handle = {0};
/* DMA 句柄结构体：用于配置 DMA 参数 */
DMA_HandleTypeDef dma_handle = {0};

uint16_t adc_value = 0;

/**
 * @brief  ADC 初始化函数
 * @note   配置 ADC 工作模式为：单次转换、非扫描、软件触发
 */
void adc_init(void)
{
    adc_handle.Instance = ADC1;
    adc_handle.Init.DataAlign = ADC_DATAALIGN_RIGHT;            /* 数据右对齐 */
    adc_handle.Init.ScanConvMode = ADC_SCAN_DISABLE;            /* 非扫描模式（仅单通道） */
    adc_handle.Init.ContinuousConvMode = ENABLE;                /* 开启连续转换模式（与注释原意“单次”不同，代码为Enable即连续） */
    adc_handle.Init.NbrOfConversion = 1;                        /* 转换通道数：1个 */
    adc_handle.Init.DiscontinuousConvMode = DISABLE;            /* 禁止间断模式 */
    adc_handle.Init.NbrOfDiscConversion = 0;
    adc_handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;      /* 软件触发 */
    
    // 应用上述配置
    HAL_ADC_Init(&adc_handle);
    
    // 【关键】执行 ADC 自校准
    // 上电初始化后必须校准一次，消除芯片制造误差，提高精度
    HAL_ADCEx_Calibration_Start(&adc_handle);
}

void dma_init()
{
    /* 1. 使能 DMA1 时钟 */
    __HAL_RCC_DMA1_CLK_ENABLE();
    
    /* 2. 配置 DMA 传输实例：STM32F103 的 USART1_TX 固定连接在 DMA1 通道 4 */
    dma_handle.Instance = DMA1_Channel1;
    
    /* 3. 设置传输方向：从内存到外设（串口发送数据） */
    dma_handle.Init.Direction = DMA_PERIPH_TO_MEMORY;
    
    /* 4. 存储器（内存）配置 */
    dma_handle.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;         /* 内存数据宽度：16位（半字），适配ADC的12位精度 */
    dma_handle.Init.MemInc = DMA_MINC_ENABLE;                           /* 内存地址自增：存储多个数据时指针自动后移 */
    
    /* 5. 外设（串口）配置 */
    dma_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;      /* 外设数据宽度：16位（半字） */
    dma_handle.Init.PeriphInc = DMA_PINC_DISABLE;                       /* 外设地址不自增：始终指向串口的数据寄存器（DR） */
    
    /* 6. 传输模式与优先级配置 */
    dma_handle.Init.Priority = DMA_PRIORITY_MEDIUM;                     /* 优先级：中等 */
    dma_handle.Init.Mode = DMA_CIRCULAR;                                /* 循环模式：不断搬运数据，不会停止 */
    /* 7. 执行 DMA 初始化 */
    HAL_DMA_Init(&dma_handle);
    
    /* 8. 关联句柄：将 DMA 句柄与串口句柄的发送 DMA 指针（hdmatx）链接起来 */
    __HAL_LINKDMA(&adc_handle,DMA_Handle,dma_handle);
    
}


/**
 * @brief  ADC 底层硬件初始化回调函数
 * @note   此函数会被 HAL_ADC_Init 自动调用，负责开启时钟和配置 GPIO
 */
void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
    if(hadc->Instance == ADC1)
    {
        RCC_PeriphCLKInitTypeDef adc_clk_init = {0};
        GPIO_InitTypeDef gpio_init_struct = {0};
        
        // 1. 开启外设时钟
        __HAL_RCC_ADC1_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();
        
        // 2. 配置 GPIO 引脚 (PA1)
        gpio_init_struct.Pin = GPIO_PIN_0;
        gpio_init_struct.Mode = GPIO_MODE_ANALOG;
        HAL_GPIO_Init(GPIOB,&gpio_init_struct);
        
        // 3. 配置 ADC 时钟分频
        adc_clk_init.PeriphClockSelection = RCC_PERIPHCLK_ADC;
        adc_clk_init.AdcClockSelection = RCC_ADCPCLK2_DIV6;
        HAL_RCCEx_PeriphCLKConfig(&adc_clk_init);
    }
}

/**
 * @brief  配置 ADC 通道参数
 * @param  channel: 要配置的通道 (如 ADC_CHANNEL_1)
 * @param  rank: 转换顺序 (通常为 RANK_1)
 * @param  samplingtime: 采样时间
 */
void adc_channel_config(ADC_HandleTypeDef* hadc,uint32_t channel,uint32_t rank,uint32_t samplingtime)
{
    ADC_ChannelConfTypeDef adc_ch_config = {0};
    
    adc_ch_config.Channel = channel;
    adc_ch_config.Rank = rank;
    adc_ch_config.SamplingTime = samplingtime;
    
    // 调用库函数应用配置
    HAL_ADC_ConfigChannel(hadc,&adc_ch_config);
}


/**
 * @brief  ADC与DMA 联合初始化并启动
 * @param  mar: 存储转换数据的内存地址 (Memory Address Register)
 */
void adc_dma_init(void)
{
    // 1. 初始化 ADC 基础参数
    adc_init();
    
    // 2. 配置具体通道 (通道1, 采样时间 239.5 周期)
    adc_channel_config(&adc_handle,ADC_CHANNEL_8,ADC_REGULAR_RANK_1,ADC_SAMPLETIME_239CYCLES_5);
    
    // 3. 初始化 DMA
    dma_init();
    
    // 4. 开启 ADC 的 DMA 传输模式
    HAL_ADC_Start_DMA(&adc_handle,(uint32_t *)&adc_value,1);// 传输长度设为1，配合循环模式使用
}

//ADC采样值
float get_adc_value(void)
{
    return (float)adc_value/4096 *3.3;
}
