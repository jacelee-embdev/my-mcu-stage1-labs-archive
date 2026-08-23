#include "voice.h"

volatile uint8_t voice_rx_latch = 0;

// 语音模块初始化：配置为外部中断模式
void voice_init(void)
{
    GPIO_InitTypeDef gpio_initstruct;
    
    VOICE_GPIO_CLK_ENABLE();
    
    // 配置为：上升沿触发中断
    gpio_initstruct.Pin   = VOICE_PIN0 | VOICE_PIN1 | VOICE_PIN2;
    gpio_initstruct.Mode  = GPIO_MODE_IT_RISING; 
    gpio_initstruct.Pull  = GPIO_PULLDOWN;          // 配合脉冲信号，建议下拉
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(VOICE_GPIO_PORT, &gpio_initstruct);
    
    // 开启 EXTI15_10 中断通道 (PF11~13 都在这个通道)
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 2, 0); 
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

/**
 * @brief  EXTI15~10 中断服务函数
 * @note   PF11, PF12, PF13 触发中断时都会进入这里
 */
void EXTI15_10_IRQHandler(void)
{
    // 调用 HAL 库的通用处理接口，它会自动清除标志位并调用我们的 HAL_GPIO_EXTI_Callback
    HAL_GPIO_EXTI_IRQHandler(VOICE_PIN0); // 处理 PF11
    HAL_GPIO_EXTI_IRQHandler(VOICE_PIN1); // 处理 PF12
    HAL_GPIO_EXTI_IRQHandler(VOICE_PIN2); // 处理 PF13
}

//中断回调函数被整合到了"keyboard.c"中

// 获取语音命令：读取即复位
uint8_t voice_get_cmd(void)
{
    uint8_t temp = voice_rx_latch;
    voice_rx_latch = 0;     // 读取后复位为 0
    return temp;
}