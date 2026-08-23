#include "sys.h" 
#include "pwm_sg90.h" 

TIM_HandleTypeDef tim3_handle = {0}; 

/**
 * @brief  初始化TIM3为PWM输出模式（适配SG90舵机）
 * @note   TIM3挂载APB1总线，时钟源为72MHz；配置后PWM周期固定为20ms（SG90标准周期）
 *         预分频系数7199：72MHz/(7199+1)=10kHz（计数频率）
 *         自动重装值200：10kHz计数频率下，200个计数周期=20ms（PWM周期）
 * @retval 无
 */
void tim3_init(void) 
{
    // PWM输出比较配置结构体
    TIM_OC_InitTypeDef pwm_config = {0}; 
    
    // 配置TIM3核心参数
    tim3_handle.Instance = TIM3; 
    tim3_handle.Init.Prescaler = 7199; 
    tim3_handle.Init.Period = 200; 
    tim3_handle.Init.CounterMode = TIM_COUNTERMODE_UP; 
    HAL_TIM_PWM_Init(&tim3_handle);
    
    // 配置TIM3通道1的PWM参数
    pwm_config.OCMode = TIM_OCMODE_PWM1;        // PWM1模式：计数<CCR时输出高电平
    pwm_config.Pulse = 100; 
    pwm_config.OCPolarity = TIM_OCPOLARITY_HIGH;    // PWM输出极性为高电平有效
    HAL_TIM_PWM_ConfigChannel(&tim3_handle,&pwm_config,TIM_CHANNEL_1); 
    
    // 启动PWM输出
    HAL_TIM_PWM_Start(&tim3_handle,TIM_CHANNEL_1); 
}

/**
 * @brief  TIM3 PWM模式底层硬件初始化回调函数（HAL库内部调用）
 * @param  htim: 指向定时器句柄的指针
 * @retval 无
 */
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim) 
{
    // 仅处理TIM3的初始化
    if(htim->Instance == TIM3) 
    {
            GPIO_InitTypeDef gpio_initstruct; 
        // 使能TIM3时钟（APB1总线外设）
        __HAL_RCC_TIM3_CLK_ENABLE(); 
        // 使能GPIOB时钟（PB8属于GPIOB）
        __HAL_RCC_GPIOA_CLK_ENABLE(); 
        
        // 配置PB8引脚为TIM3_CH3复用功能
        gpio_initstruct.Pin=GPIO_PIN_6; 
        gpio_initstruct.Mode=GPIO_MODE_AF_PP;   // 模式：复用推挽输出
        gpio_initstruct.Pull=GPIO_PULLUP; 
        gpio_initstruct.Speed=GPIO_SPEED_FREQ_HIGH; 
        HAL_GPIO_Init(GPIOA,&gpio_initstruct); 
    }
}

/**
 * @brief  设置TIM3通道1的PWM比较值，调整占空比
 * @param  val: 要设置的比较值（范围0~200，与自动重装值匹配）
 * @retval 无
 */
void set_tim3_compare(uint16_t val) 
{
    // 直接修改TIM3通道3的比较值（CCR3寄存器）
    __HAL_TIM_SET_COMPARE(&tim3_handle,TIM_CHANNEL_1,val); 
} 

/**
 * @brief  SG90舵机初始化函数
 * @retval 无
 */
void sg90_init(void)
{
    tim3_init();
}

/**
 * @brief  设置SG90舵机的旋转角度
 * @param  angle: 目标旋转角度（需匹配舵机有效角度范围）
 * @retval 无
 */
void set_sg90_angle(uint16_t angle)
{
    uint16_t CCRx = (1.0/9.0) * angle+5.0 ;
    set_tim3_compare(CCRx);
}
