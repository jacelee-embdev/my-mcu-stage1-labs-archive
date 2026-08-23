#include "led.h"
#include "adc.h"
#include "delay.h"
#include "stdio.h"

float  led_level = 0;
uint16_t adc_val_lux[2] = {0};

TIM_HandleTypeDef pwm_handle = {0}; 

// PWM 基础参数初始化
void pwm_init(uint16_t arr, uint16_t psc) 
{
    TIM_OC_InitTypeDef pwm_config = {0}; 
    
    pwm_handle.Instance = LED_PWM_TIM_INSTANCE;                         // 使用宏定义实例
    pwm_handle.Init.Prescaler = psc; 
    pwm_handle.Init.Period = arr; 
    pwm_handle.Init.CounterMode = TIM_COUNTERMODE_UP; 
    HAL_TIM_PWM_Init(&pwm_handle);      
    
    // 配置 PWM 通道
    pwm_config.OCMode = TIM_OCMODE_PWM1; 
    pwm_config.Pulse = 0; 
    pwm_config.OCPolarity = TIM_OCPOLARITY_HIGH; 
    HAL_TIM_PWM_ConfigChannel(&pwm_handle, &pwm_config, LED_PWM_TIM_CHANNEL);
    
    // 启动 PWM 输出
    HAL_TIM_PWM_Start(&pwm_handle, LED_PWM_TIM_CHANNEL);
}

// 定时器底层硬件初始化 (MSP 回调)
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim) 
{
    if(htim->Instance == LED_PWM_TIM_INSTANCE)                          // 匹配宏定义实例
    {
        GPIO_InitTypeDef gpio_initstruct; 
        
        LED_PWM_TIM_CLK_ENABLE();                                       // 开启定时器时钟
        LED_PWM_GPIO_CLK_ENABLE();                                      // 开启 GPIO 时钟
        
        gpio_initstruct.Pin   = LED_PWM_GPIO_PIN;                       // 引脚号
        gpio_initstruct.Mode  = GPIO_MODE_AF_PP;                        // 复用推挽输出
        gpio_initstruct.Pull  = GPIO_PULLUP; 
        gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH; 
        HAL_GPIO_Init(LED_PWM_GPIO_PORT, &gpio_initstruct);
    }
}

// 设置 PWM 占空比
void set_pwm_compare(uint16_t val) 
{
    __HAL_TIM_SET_COMPARE(&pwm_handle, LED_PWM_TIM_CHANNEL, val);
}

// LED 初始化：频率 2kHz (72M / 72 / 500)
void led_init(void)
{
    pwm_init(500 - 1, 72 - 1);
}

void led_on(void)
{
    set_pwm_compare(0+450*led_level);
}

void led_off(void)
{
    set_pwm_compare(0);
}



void led_brightness_up(void)
{
    if(led_level < 1.0)
    {
        led_level += 0.1;
    }
    
    set_pwm_compare(0+450*led_level);
}

void led_brightness_down(void)
{
    if(led_level > 0.0)
    {
        led_level -= 0.1;
    }
    
    set_pwm_compare(0+450*led_level);
}

void led_brightness_auto(float lux_val)
{
    led_level =lux_val/3.3;
    set_pwm_compare(0+450*led_level);
}

void led_test(void)
{
    led_on();
    delay_ms(1000);
    
    led_off();
    delay_ms(1000);
    
    led_brightness_up();
    delay_ms(1000);
    
    led_brightness_down();
    delay_ms(1000);
    
}
