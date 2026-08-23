#include "led.h"

// 初始化GPIO
void led_init(void)
{
    GPIO_InitTypeDef gpio_initstruct;

    // 开启时钟
    LED_CLK_ENABLE();

    // 配置GPIO参数
    gpio_initstruct.Pin = LED_PIN;
    gpio_initstruct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_initstruct.Pull = GPIO_PULLUP;
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LED_PORT, &gpio_initstruct);

    // 默认关闭LED
    led_off();
}

// 点亮LED
void led_on(void)
{
    HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET);
}

// 熄灭LED
void led_off(void)
{
    HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_SET);
}

// 翻转LED状态
void led_toggle(void)
{
    HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
}
