/**
 * @file    encoder.c
 * @brief   正交编码器驱动源文件 - 实现基于硬件定时器的正交解码
 */

/* Includes ------------------------------------------------------------------*/
#include "encoder.h"

/* ================================================================================= */
/* [私有变量与句柄] 封装模块内部使用的硬件状态句柄                                   */
/* ================================================================================= */
static TIM_HandleTypeDef s_encoder_left_handle  = {0};                          // 左编码器定时器抽象层句柄
static TIM_HandleTypeDef s_encoder_right_handle = {0};                          // 右编码器定时器抽象层句柄

/* ================================================================================= */
/* [私有底层驱动] 负责内部硬件级初始化逻辑                                           */
/* ================================================================================= */

/**
 * @brief  初始化左侧正交编码器接口配置
 * @note   配置为 TI1 和 TI2 双边沿计数模式（4倍频），应用输入滤波去除毛刺
 */
static void encoder_left_hardware_init(void)
{
    TIM_Encoder_InitTypeDef encoder_config = {0};
    
    /* 1. 时基单元配置：建立基础计数环境 */
    s_encoder_left_handle.Instance           = ENCODER_LEFT_TIM;
    s_encoder_left_handle.Init.Period        = ENCODER_TIM_RELOAD_MAX;
    s_encoder_left_handle.Init.Prescaler     = 0;                               // 编码器模式依赖实际边沿脉冲，无需时钟分频
    s_encoder_left_handle.Init.CounterMode   = TIM_COUNTERMODE_UP;
    s_encoder_left_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    
    /* 2. 正交解码模式配置：启用双通道解析实现4倍频 */
    encoder_config.EncoderMode               = TIM_ENCODERMODE_TI12;
    
    /* A相通道匹配与滤波配置 */
    encoder_config.IC1Polarity               = TIM_ICPOLARITY_FALLING;           // 捕获极性与外部信号电平逻辑保持一致
    encoder_config.IC1Selection              = TIM_ICSELECTION_DIRECTTI;
    encoder_config.IC1Prescaler              = TIM_ICPSC_DIV1;
    encoder_config.IC1Filter                 = ENCODER_INPUT_FILTER_VAL;        // 拦截高频电磁干扰或机械振铃
    
    /* B相通道匹配与滤波配置 */
    encoder_config.IC2Polarity               = TIM_ICPOLARITY_RISING;
    encoder_config.IC2Selection              = TIM_ICSELECTION_DIRECTTI;
    encoder_config.IC2Prescaler              = TIM_ICPSC_DIV1;
    encoder_config.IC2Filter                 = ENCODER_INPUT_FILTER_VAL;
    
    /* 3. 固化配置并开启硬件计数 */
    HAL_TIM_Encoder_Init(&s_encoder_left_handle, &encoder_config);
    HAL_TIM_Encoder_Start(&s_encoder_left_handle, TIM_CHANNEL_ALL);
}

/**
 * @brief  初始化右侧正交编码器接口配置
 * @note   配置为 TI1 和 TI2 双边沿计数模式（4倍频），应用输入滤波去除毛刺
 */
static void encoder_right_hardware_init(void)
{
    TIM_Encoder_InitTypeDef encoder_config = {0};
    
    /* 1. 时基单元配置：建立基础计数环境 */
    s_encoder_right_handle.Instance           = ENCODER_RIGHT_TIM;
    s_encoder_right_handle.Init.Period        = ENCODER_TIM_RELOAD_MAX;
    s_encoder_right_handle.Init.Prescaler     = 0;
    s_encoder_right_handle.Init.CounterMode   = TIM_COUNTERMODE_UP;
    s_encoder_right_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    
    /* 2. 正交解码模式配置：启用双通道解析实现4倍频 */
    encoder_config.EncoderMode                = TIM_ENCODERMODE_TI12;
    
    /* A相通道匹配与滤波配置 */
    encoder_config.IC1Polarity                = TIM_ICPOLARITY_FALLING;
    encoder_config.IC1Selection               = TIM_ICSELECTION_DIRECTTI;
    encoder_config.IC1Prescaler               = TIM_ICPSC_DIV1;
    encoder_config.IC1Filter                  = ENCODER_INPUT_FILTER_VAL;
    
    /* B相通道匹配与滤波配置 */
    encoder_config.IC2Polarity                = TIM_ICPOLARITY_RISING;
    encoder_config.IC2Selection               = TIM_ICSELECTION_DIRECTTI;
    encoder_config.IC2Prescaler               = TIM_ICPSC_DIV1;
    encoder_config.IC2Filter                  = ENCODER_INPUT_FILTER_VAL;
    
    /* 3. 固化配置并开启硬件计数 */
    HAL_TIM_Encoder_Init(&s_encoder_right_handle, &encoder_config);
    HAL_TIM_Encoder_Start(&s_encoder_right_handle, TIM_CHANNEL_ALL);
}

/* ================================================================================= */
/* [物理层] 负责硬件外设的底层时序与引脚初始化                                       */
/* ================================================================================= */

/**
 * @brief  TIM 编码器接口 MSP 初始化回调
 * @note   此函数由 HAL_TIM_Encoder_Init 内部调用，分配引脚资源与时钟总线
 * @param  htim: 定时器句柄指针
 */
void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef *htim)
{
    GPIO_InitTypeDef gpio_init_config = {0};

    if (htim->Instance == ENCODER_LEFT_TIM)
    {
        /* 1. 挂载时钟总线 */
        ENCODER_LEFT_TIM_CLK_ENABLE();
        ENCODER_LEFT_GPIO_CLK_ENABLE();
        
        /* 2. 映射引脚复用功能 */
        gpio_init_config.Pin   = ENCODER_LEFT_PIN_A | ENCODER_LEFT_PIN_B;
        gpio_init_config.Mode  = GPIO_MODE_INPUT;
        gpio_init_config.Pull  = GPIO_PULLUP;                                   // 钳制默认电平，抵抗悬空噪声
        gpio_init_config.Speed = GPIO_SPEED_FREQ_HIGH;                          // 匹配电机高速旋转时的频宽需求
        
        HAL_GPIO_Init(ENCODER_LEFT_GPIO_PORT, &gpio_init_config);
    }
    else if (htim->Instance == ENCODER_RIGHT_TIM)
    {
        /* 1. 挂载时钟总线 */
        ENCODER_RIGHT_TIM_CLK_ENABLE();
        ENCODER_RIGHT_GPIO_CLK_ENABLE();
        
        /* 2. 映射引脚复用功能 */
        gpio_init_config.Pin   = ENCODER_RIGHT_PIN_A | ENCODER_RIGHT_PIN_B;
        gpio_init_config.Mode  = GPIO_MODE_INPUT;
        gpio_init_config.Pull  = GPIO_PULLUP;
        gpio_init_config.Speed = GPIO_SPEED_FREQ_HIGH;
        
        HAL_GPIO_Init(ENCODER_RIGHT_GPIO_PORT, &gpio_init_config);
    }
}

/* ================================================================================= */
/* [核心业务接口] 提供给外部业务逻辑调用的功能接口                                   */
/* ================================================================================= */

void encoder_init(void)
{
    encoder_left_hardware_init();
    encoder_right_hardware_init();
}

int16_t encoder_left_get_delta(void)
{
    /* 提取并转换硬件累加器数据以判断旋转方向与步数 */
    int16_t delta_count = (int16_t)__HAL_TIM_GET_COUNTER(&s_encoder_left_handle);
    
    /* 复位游标状态，建立下次采样的差分基准 */
    __HAL_TIM_SET_COUNTER(&s_encoder_left_handle, 0);
    
    return delta_count;
}

int16_t encoder_right_get_delta(void)
{
    /* 提取并转换硬件累加器数据以判断旋转方向与步数 */
    int16_t delta_count = (int16_t)__HAL_TIM_GET_COUNTER(&s_encoder_right_handle);
    
    /* 复位游标状态，建立下次采样的差分基准 */
    __HAL_TIM_SET_COUNTER(&s_encoder_right_handle, 0);
    
    return delta_count;
}
