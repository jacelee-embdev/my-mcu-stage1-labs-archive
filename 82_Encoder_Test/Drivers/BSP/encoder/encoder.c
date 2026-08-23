/**
 * @file    encoder.c
 * @brief   正交编码器驱动源文件 - 实现基于硬件定时器的正交解码
 */

/* Includes ------------------------------------------------------------------*/
#include "encoder.h"

/* [私有变量与句柄] 作用是封装模块内部使用的硬件状态句柄 -------------------------*/
static TIM_HandleTypeDef g_encoder_tim_handle = {0};                            // 定时器硬件抽象层句柄

/* ================================================================================= */
/* [物理层] 负责硬件外设的底层底层时序与引脚初始化                                         */
/* ================================================================================= */

/**
 * @brief  TIM 编码器接口 MSP 初始化回调
 * @note   此函数由 HAL_TIM_Encoder_Init 内部调用，负责 GPIO 与时钟的物理层配置
 * @param  htim: 定时器句柄指针
 */
void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef *htim)
{
    GPIO_InitTypeDef gpio_initstruct = {0};

    if (htim->Instance == ENCODER_TIM)
    {
        /* 1. 使能外设时钟 */
        ENCODER_TIM_CLK_ENABLE();
        ENCODER_GPIO_CLK_ENABLE();
        
        /* 2. 配置编码器输入引脚 (PB6/PB7) */
        gpio_initstruct.Pin   = ENCODER_PIN_A | ENCODER_PIN_B;
        gpio_initstruct.Mode  = GPIO_MODE_INPUT;                                // 编码器输入模式
        gpio_initstruct.Pull  = GPIO_PULLUP;                                   // 上拉以增强抗干扰能力
        gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;                           // 响应高频脉冲
        
        HAL_GPIO_Init(ENCODER_GPIO_PORT, &gpio_initstruct);
    }
}

/* ================================================================================= */
/* [应用层] 提供给外部业务逻辑调用的功能接口                                            */
/* ================================================================================= */

/**
 * @brief  初始化正交编码器接口配置
 * @note   配置为 TI1 和 TI2 双边沿计数模式（4倍频），并应用输入滤波以去除毛刺
 */
void encoder_init(void)
{
    TIM_Encoder_InitTypeDef encoder_config = {0};
    
    /* 1. 基础时基单元配置 */
    g_encoder_tim_handle.Instance           = ENCODER_TIM;
    g_encoder_tim_handle.Init.Period        = ENCODER_RELOAD_VALUE;             // 设定计数溢出上限
    g_encoder_tim_handle.Init.Prescaler     = 0;                                // 编码器模式下预分频固定为0
    g_encoder_tim_handle.Init.CounterMode   = TIM_COUNTERMODE_UP;               // 初始向上计数
    g_encoder_tim_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    
    /* 2. 正交解码模式配置 */
    encoder_config.EncoderMode              = TIM_ENCODERMODE_TI12;             // TI1/TI2均计数，实现4倍频解析度
    
    /* A相输入通道配置 */
    encoder_config.IC1Polarity              = TIM_ICPOLARITY_RISING;            // 极性不反相
    encoder_config.IC1Selection             = TIM_ICSELECTION_DIRECTTI;         // 直接映射到 TI1
    encoder_config.IC1Prescaler             = TIM_ICPSC_DIV1;                   // 不分频
    encoder_config.IC1Filter                = ENCODER_IC_FILTER;                // 设置滤波器防止机械振铃或噪声
    
    /* B相输入通道配置 */
    encoder_config.IC2Polarity              = TIM_ICPOLARITY_RISING;            // 极性不反相
    encoder_config.IC2Selection             = TIM_ICSELECTION_DIRECTTI;         // 直接映射到 TI2
    encoder_config.IC2Prescaler             = TIM_ICPSC_DIV1;
    encoder_config.IC2Filter                = ENCODER_IC_FILTER;
    
    /* 3. 应用配置并启动编码器计数 */
    HAL_TIM_Encoder_Init(&g_encoder_tim_handle, &encoder_config);
    HAL_TIM_Encoder_Start(&g_encoder_tim_handle, TIM_CHANNEL_ALL);
}

/**
 * @brief  获取当前编码器增量计数值并清零
 * @note   通过读取 CNT 寄存器获取自上次调用以来的脉冲差值，常用于 PID 速度采样
 * @retval int16_t: 增量计数值 (支持正负，反映旋转方向)
 */
int16_t encoder_get_count_delta(void)
{
    // 获取 16 位计数器的当前值并强制转换为带符号整型
    int16_t temp = (int16_t)__HAL_TIM_GET_COUNTER(&g_encoder_tim_handle);
    
    // 软件清零计数器，以便下一次采样获取的是纯增量（Delta值）
    __HAL_TIM_SET_COUNTER(&g_encoder_tim_handle, 0);
    
    return temp;
}
