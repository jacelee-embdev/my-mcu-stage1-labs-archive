#include "relay_fan.h"
#include "delay.h"

// 初始化 GPIO
void relay_fan_init(void)
{
    GPIO_InitTypeDef gpio_initstruct;
    
    RELAY_FAN_GPIO_CLK_ENABLE();                // 使能时钟
    
    gpio_initstruct.Pin   = RELAY_FAN_GPIO_PIN; // 引脚号
    gpio_initstruct.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio_initstruct.Pull  = GPIO_PULLUP;
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(RELAY_FAN_GPIO_PORT, &gpio_initstruct);
    
    relay_fan_off();                            // 默认关闭
}
    
// 开启风扇
void relay_fan_on(void)
{
    HAL_GPIO_WritePin(RELAY_FAN_GPIO_PORT, RELAY_FAN_GPIO_PIN, GPIO_PIN_SET);
}

// 关闭风扇
void relay_fan_off(void)
{
    HAL_GPIO_WritePin(RELAY_FAN_GPIO_PORT, RELAY_FAN_GPIO_PIN, GPIO_PIN_RESET);
}

// 获取风扇状态
uint8_t relay_fan_status_get(void)
{
    return (uint8_t)HAL_GPIO_ReadPin(RELAY_FAN_GPIO_PORT, RELAY_FAN_GPIO_PIN);
}

void relay_fan_test(void)
{
    relay_fan_on();
    delay_ms(500);
    relay_fan_off();
    delay_ms(500);
}
