#include "iwdg.h"
#include "sys.h"
#include "uart1.h"

IWDG_HandleTypeDef iwdg_handle = {0};

void iwdg_init(uint8_t psc,uint16_t rlr)
{
//    IWDG->KR = 0x5555;    // 使能寄存器访问（解除写保护）
//    IWDG->PR = psc;       // 设置分频
//    IWDG->RLR = rlr;      // 设置重装载值
//    IWDG->KR = 0xAAAA;    // 喂狗（将 RLR 加载到计数器）
//    IWDG->KR = 0xCCCC;    // 启动看门狗（关键指令！）
    iwdg_handle.Instance = IWDG;
    iwdg_handle.Init.Prescaler = psc;
    iwdg_handle.Init.Reload = rlr;
    HAL_IWDG_Init(&iwdg_handle);
}

void iwdg_feed(void)
{
    HAL_IWDG_Refresh(&iwdg_handle);
}


void iwdg_test(void)
{
    if (HAL_IWDG_Init(&iwdg_handle) != HAL_OK)
    {
        printf("IWDG 初始化失败！\n");
        while(1); 
    }
}
