#include "adc.h"
#include "string.h"

ADC_HandleTypeDef adc_handle = {0};
DMA_HandleTypeDef dma_handle = {0};
uint16_t adc_result[2] = {0};           // 存放 2 个通道的转换结果

// ADC 基础配置
void adc_init(void)
{
    adc_handle.Instance = ADC_INSTANCE;
    adc_handle.Init.DataAlign = ADC_DATAALIGN_RIGHT;            
    adc_handle.Init.ScanConvMode = ADC_SCAN_ENABLE;             // 扫描模式（多通道）
    adc_handle.Init.ContinuousConvMode = ENABLE;                // 连续转换模式
    adc_handle.Init.NbrOfConversion = 2;                        // 转换通道数：2
    adc_handle.Init.DiscontinuousConvMode = DISABLE;            
    adc_handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;      // 软件触发
    
    HAL_ADC_Init(&adc_handle);
    HAL_ADCEx_Calibration_Start(&adc_handle);                   // ADC 校准
}

// DMA 配置
void dma_init(void)
{
    ADC_DMA_CLK_ENABLE();                                       // DMA 时钟使能
    
    dma_handle.Instance = ADC_DMA_INSTANCE;                     // 定位 DMA 通道
    dma_handle.Init.Direction = DMA_PERIPH_TO_MEMORY;           // 外设到内存
    dma_handle.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD; // 内存 16 位对齐
    dma_handle.Init.MemInc = DMA_MINC_ENABLE;                   // 内存地址自增
    dma_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    dma_handle.Init.PeriphInc = DMA_PINC_DISABLE;               
    dma_handle.Init.Priority = DMA_PRIORITY_MEDIUM;             
    dma_handle.Init.Mode = DMA_CIRCULAR;                        // 循环模式
    
    HAL_DMA_Init(&dma_handle);
    __HAL_LINKDMA(&adc_handle, DMA_Handle, dma_handle);         // 关联 ADC 和 DMA
}

// 底层硬件初始化 (MSP)
void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
    if(hadc->Instance == ADC_INSTANCE)
    {
        RCC_PeriphCLKInitTypeDef adc_clk_init = {0};
        GPIO_InitTypeDef gpio_init_struct = {0};
        
        ADC_CLK_ENABLE();                                       // 开启 ADC 时钟
        ADC_GPIO_CLK_ENABLE();                                  // 开启 GPIO 时钟
        
        // 配置引脚为模拟模式
        gpio_init_struct.Pin = ADC_CH0_PIN | ADC_CH1_PIN;
        gpio_init_struct.Mode = GPIO_MODE_ANALOG;
        HAL_GPIO_Init(ADC_GPIO_PORT, &gpio_init_struct);
        
        // ADC 时钟 6 分频 (72M/6 = 12M)
        adc_clk_init.PeriphClockSelection = RCC_PERIPHCLK_ADC;
        adc_clk_init.AdcClockSelection = RCC_ADCPCLK2_DIV6;
        HAL_RCCEx_PeriphCLKConfig(&adc_clk_init);
    }
}

// ADC 与 DMA 联合启动
void adc_dma_init(void)
{
    adc_init();
    
    // 配置通道转换顺序及采样时间
    ADC_ChannelConfTypeDef ch_cfg = {0};
    ch_cfg.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
    
    ch_cfg.Channel = ADC_CHANNEL_0;
    ch_cfg.Rank = ADC_REGULAR_RANK_1;
    HAL_ADC_ConfigChannel(&adc_handle, &ch_cfg);
    
    ch_cfg.Channel = ADC_CHANNEL_1;
    ch_cfg.Rank = ADC_REGULAR_RANK_2;
    HAL_ADC_ConfigChannel(&adc_handle, &ch_cfg);
    
    dma_init();
    
    // 启动 ADC DMA 传输
    HAL_ADC_Start_DMA(&adc_handle, (uint32_t *)adc_result, 2);
}

// 获取最新的 ADC 结果
void get_adc_result(uint16_t *result)
{
    memcpy(result, adc_result, sizeof(adc_result));
}
