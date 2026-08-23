#ifndef __ADC_H__
#define __ADC_H__

#include "sys.h"

/* --- 硬件接口定义 --- */
#define ADC_INSTANCE                ADC1                            // ADC 外设实例
#define ADC_CLK_ENABLE()            __HAL_RCC_ADC1_CLK_ENABLE()     // ADC 时钟使能

#define ADC_GPIO_PORT               GPIOA                           // GPIO 端口
#define ADC_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOA_CLK_ENABLE()    // GPIO 时钟使能
#define ADC_CH0_PIN                 GPIO_PIN_0                      // 通道 0 引脚
#define ADC_CH1_PIN                 GPIO_PIN_1                      // 通道 1 引脚

#define ADC_DMA_INSTANCE            DMA1_Channel1                   // DMA 通道实例
#define ADC_DMA_CLK_ENABLE()        __HAL_RCC_DMA1_CLK_ENABLE()     // DMA 时钟使能

/* --- 函数声明 --- */
void adc_dma_init(void);                // ADC+DMA 联合初始化
void get_adc_result(uint16_t *result);  // 获取转换结果

#endif
