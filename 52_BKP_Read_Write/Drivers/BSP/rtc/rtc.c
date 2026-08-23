#include "rtc.h"

RTC_HandleTypeDef rtc_handle = {0};

void rtc_init(void)
{
    __HAL_RCC_PWR_CLK_ENABLE();     //使能PWR时钟
    __HAL_RCC_BKP_CLK_ENABLE();     //使能BKP时钟
    HAL_PWR_EnableBkUpAccess();     //取消备份域保护
    
    rtc_handle.Instance = RTC;      //RTC基地址
    rtc_handle.Init.AsynchPrediv = 32767;   //异步预分频(32.768KHz->1Hz)
    rtc_handle.Init.OutPut = RTC_OUTPUTSOURCE_NONE;     //禁止RTC引脚输出
    HAL_RTC_Init(&rtc_handle);          //初始化RTC
}

uint16_t rtc_read_bkr(uint8_t bkr_x)
{
    uint32_t data = 0;
    data = HAL_RTCEx_BKUPRead(&rtc_handle,bkr_x);   //读取备份寄存器数据
    return (uint16_t)data;
}

void rtc_write_bkr(uint8_t bkr_x,uint16_t data)
{
    HAL_RTCEx_BKUPWrite(&rtc_handle,bkr_x,data);    //向备份寄存器写入数据
}
