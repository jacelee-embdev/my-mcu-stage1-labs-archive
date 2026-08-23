#include "relay_lock.h"
#include "delay.h"

/**
 * @brief 初始化继电器控制引脚
 */
void relay_lock_init(void)
{
    GPIO_InitTypeDef gpio_initstruct;

    RELAY_LOCK_CLK_ENABLE();

    gpio_initstruct.Pin = RELAY_LOCK_PIN;
    gpio_initstruct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_initstruct.Pull = GPIO_PULLUP;
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(RELAY_LOCK_PORT, &gpio_initstruct);

    relay_lock_off(); // 初始状态设为关闭
}

// 打开继电器
void relay_lock_on(void)
{
    HAL_GPIO_WritePin(RELAY_LOCK_PORT, RELAY_LOCK_PIN, RELAY_LOCK_ON_LEVEL);
}

// 关闭继电器
void relay_lock_off(void)
{
    HAL_GPIO_WritePin(RELAY_LOCK_PORT, RELAY_LOCK_PIN, RELAY_LOCK_OFF_LEVEL);
}

/**
 * @brief 获取引脚当前状态 (0:低电平, 1:高电平)
 */
uint8_t relay_lock_status_get(void)
{
    return (uint8_t)HAL_GPIO_ReadPin(RELAY_LOCK_PORT, RELAY_LOCK_PIN);
}

// 测试函数
void relay_lock_test(void)
{
    relay_lock_on();
    delay_ms(1000);
    relay_lock_off();
    delay_ms(1000);
}
