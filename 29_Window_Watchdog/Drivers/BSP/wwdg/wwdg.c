#include "wwdg.h"
#include "led.h"


WWDG_HandleTypeDef wwdg_handle = {0};

// WWDG 初始化：设置计数器初值、窗口值和分频
void wwdg_init(uint8_t tr,uint8_t wr,uint32_t psc)
{
    wwdg_handle.Instance =  WWDG;                   
    wwdg_handle.Init.Counter = tr;                  // 计数器初值 (最大 0x7F)
    wwdg_handle.Init.Window = wr;                   // 窗口上限值 (必须 < 0x80)
    wwdg_handle.Init.Prescaler = psc;               // 预分频系数
    wwdg_handle.Init.EWIMode = WWDG_EWI_ENABLE;     // 开启提前唤醒中断 (EWI)
    HAL_WWDG_Init(&wwdg_handle);
}

// 硬件底层初始化：时钟与中断配置
void HAL_WWDG_MspInit(WWDG_HandleTypeDef *hwwdg)
{
    __HAL_RCC_WWDG_CLK_ENABLE();            // 使能 WWDG 时钟
    HAL_NVIC_SetPriority(WWDG_IRQn,2,2);    // 设置中断优先级
    HAL_NVIC_EnableIRQ(WWDG_IRQn);          // 使能 NVIC 中断通道
}

// 中断入口函数
void WWDG_IRQHandler(void)
{
    HAL_WWDG_IRQHandler(&wwdg_handle);
}

// EWI 回调函数：计数器降到 0x40 时触发
void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef *hwwdg)
{
    wwdg_feed();
    Led2Toggle();
}

// 喂狗函数
void wwdg_feed(void )
{
    HAL_WWDG_Refresh(&wwdg_handle);
}
