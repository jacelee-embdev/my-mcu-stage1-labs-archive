#include "keyboard.h"
#include "delay.h"
#include "stdio.h"
#include "voice.h"

static volatile uint8_t g_key_value = 0;
extern volatile uint8_t voice_rx_latch; // 声明外部变量

// 键值映射表 (4x4矩阵)
static const uint8_t KEY_MAP[4][4] = 
{
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// 配置为空闲检测模式：行配置为中断输入(上拉)，列输出低电平
static void Keyboard_Config_Idle(void)
{
    GPIO_InitTypeDef gpio_initstruct;

    gpio_initstruct.Pin = KBD_ROW1_PIN | KBD_ROW2_PIN | KBD_ROW3_PIN | KBD_ROW4_PIN;
    gpio_initstruct.Mode = GPIO_MODE_IT_FALLING; 
    gpio_initstruct.Pull = GPIO_PULLUP;
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(KBD_PORT, &gpio_initstruct);
    
    gpio_initstruct.Pin = KBD_COL1_PIN | KBD_COL2_PIN | KBD_COL3_PIN | KBD_COL4_PIN;
    gpio_initstruct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_initstruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(KBD_PORT, &gpio_initstruct);
    
    HAL_GPIO_WritePin(KBD_PORT, KBD_COL1_PIN | KBD_COL2_PIN | KBD_COL3_PIN | KBD_COL4_PIN, GPIO_PIN_RESET);
}

// 配置为扫描读取模式：行配置为推挽输出，列配置为输入(上拉)
static void Keyboard_Config_Scan(void)
{
    GPIO_InitTypeDef gpio_initstruct;

    gpio_initstruct.Pin = KBD_ROW1_PIN | KBD_ROW2_PIN | KBD_ROW3_PIN | KBD_ROW4_PIN;
    gpio_initstruct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_initstruct.Pull = GPIO_NOPULL;
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(KBD_PORT, &gpio_initstruct);
    
    gpio_initstruct.Pin = KBD_COL1_PIN | KBD_COL2_PIN | KBD_COL3_PIN | KBD_COL4_PIN;
    gpio_initstruct.Mode = GPIO_MODE_INPUT;
    gpio_initstruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(KBD_PORT, &gpio_initstruct);
}

void keyboard_init(void)
{
    KBD_PORT_CLK_ENABLE();
    
    // 初始化为中断等待模式
    Keyboard_Config_Idle();
    
    // 配置行引脚对应的中断优先级
    HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
    
    HAL_NVIC_SetPriority(EXTI1_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(EXTI1_IRQn);
    
    HAL_NVIC_SetPriority(EXTI2_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(EXTI2_IRQn);
    
    HAL_NVIC_SetPriority(EXTI3_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);
}

void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KBD_ROW1_PIN);
}

void EXTI1_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KBD_ROW2_PIN);
}

void EXTI2_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KBD_ROW3_PIN);
}

void EXTI3_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KBD_ROW4_PIN);
}

// 整合后的统一外部中断回调函数
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    /* ================================================================ */
    /* 1. 语音模块处理 (PF11, PF12, PF13, PF14) */
    /* ================================================================ */
    if(GPIO_Pin == VOICE_PIN0 || GPIO_Pin == VOICE_PIN1 || 
       GPIO_Pin == VOICE_PIN2 || GPIO_Pin == VOICE_PIN3)
    {
        uint8_t current_val = 0;
        
        // 合并四位指令电平 (从原来的 3 位扩展到 4 位)
        if(HAL_GPIO_ReadPin(VOICE_GPIO_PORT, VOICE_PIN3) == GPIO_PIN_SET) current_val |= (1 << 3); // 最高位
        if(HAL_GPIO_ReadPin(VOICE_GPIO_PORT, VOICE_PIN2) == GPIO_PIN_SET) current_val |= (1 << 2);
        if(HAL_GPIO_ReadPin(VOICE_GPIO_PORT, VOICE_PIN1) == GPIO_PIN_SET) current_val |= (1 << 1);
        if(HAL_GPIO_ReadPin(VOICE_GPIO_PORT, VOICE_PIN0) == GPIO_PIN_SET) current_val |= (1 << 0);
        
        if(current_val != 0) voice_rx_latch = current_val; // 锁存
        return; // 处理完语音直接退出，不进入键盘逻辑
    }

    /* ================================================================ */
    /* 2. 键盘模块处理 (KBD_ROW1~4) */
    /* ================================================================ */
    else if(GPIO_Pin == KBD_ROW1_PIN || GPIO_Pin == KBD_ROW2_PIN || 
            GPIO_Pin == KBD_ROW3_PIN || GPIO_Pin == KBD_ROW4_PIN)
    {
        int8_t row_idx = -1;
        int8_t col_idx = -1;
        
        delay_ms(10); // 键盘消抖
        
        if(HAL_GPIO_ReadPin(KBD_PORT, GPIO_Pin) != GPIO_PIN_RESET) return;

        if(GPIO_Pin == KBD_ROW1_PIN)      row_idx = 0;
        else if(GPIO_Pin == KBD_ROW2_PIN) row_idx = 1;
        else if(GPIO_Pin == KBD_ROW3_PIN) row_idx = 2;
        else if(GPIO_Pin == KBD_ROW4_PIN) row_idx = 3;
        
        if(row_idx == -1) return;

        // 执行行列扫描
        Keyboard_Config_Scan(); 
        HAL_GPIO_WritePin(KBD_PORT, KBD_ROW1_PIN|KBD_ROW2_PIN|KBD_ROW3_PIN|KBD_ROW4_PIN, GPIO_PIN_SET);
        
        uint16_t target_row_pin = (row_idx == 0) ? KBD_ROW1_PIN : 
                                  (row_idx == 1) ? KBD_ROW2_PIN : 
                                  (row_idx == 2) ? KBD_ROW3_PIN : KBD_ROW4_PIN;
        HAL_GPIO_WritePin(KBD_PORT, target_row_pin, GPIO_PIN_RESET);
        
        if(HAL_GPIO_ReadPin(KBD_PORT, KBD_COL1_PIN) == GPIO_PIN_RESET)      col_idx = 0;
        else if(HAL_GPIO_ReadPin(KBD_PORT, KBD_COL2_PIN) == GPIO_PIN_RESET) col_idx = 1;
        else if(HAL_GPIO_ReadPin(KBD_PORT, KBD_COL3_PIN) == GPIO_PIN_RESET) col_idx = 2;
        else if(HAL_GPIO_ReadPin(KBD_PORT, KBD_COL4_PIN) == GPIO_PIN_RESET) col_idx = 3;
        
        if(row_idx >= 0 && col_idx >= 0) g_key_value = KEY_MAP[row_idx][col_idx];

        Keyboard_Config_Idle();
        __HAL_GPIO_EXTI_CLEAR_IT(KBD_ROW1_PIN | KBD_ROW2_PIN | KBD_ROW3_PIN | KBD_ROW4_PIN);
    }
}

// 获取并清除当前键值
uint8_t keyboard_get_value(void)
{
    uint8_t ch = 0;
    if(g_key_value != 0)
    {
        ch = g_key_value;
        g_key_value = 0;
    }
    return ch;
}

//键盘功能测试函数
uint8_t key_val_test = 100;
void keboard_test(void)
{
    key_val_test = keyboard_get_value();
    printf("key_val:%c\r\n",key_val_test);
}
