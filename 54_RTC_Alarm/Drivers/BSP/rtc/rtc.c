#include "rtc.h"
#include "stdio.h"

RTC_HandleTypeDef rtc_handle = {0};

/* 初始化RTC：配置时钟与分频 */
void rtc_init(void)
{
    /* 开启电源与备份时钟，允许访问备份域 */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_RCC_BKP_CLK_ENABLE();
    HAL_PWR_EnableBkUpAccess();
    
    /* 配置RTC参数 */
    rtc_handle.Instance = RTC;
    rtc_handle.Init.AsynchPrediv = 32767;
    rtc_handle.Init.OutPut = RTC_OUTPUTSOURCE_NONE;

    HAL_RTC_Init(&rtc_handle);          
}

/* RTC底层初始化：配置LSE与中断 */
void HAL_RTC_MspInit(RTC_HandleTypeDef *hrtc)
{
    RCC_OscInitTypeDef osc_initstruct = {0};
    RCC_PeriphCLKInitTypeDef periphclk_initstruct = {0};
    
    /* 开启RTC时钟 */
    __HAL_RCC_RTC_ENABLE();
    
    /* 配置LSE作为时钟源 */
    osc_initstruct.OscillatorType = RCC_OSCILLATORTYPE_LSE;
    osc_initstruct.LSEState = RCC_LSE_ON;
    osc_initstruct.PLL.PLLState = RCC_PLL_NONE;
    HAL_RCC_OscConfig(&osc_initstruct);

   /* 关联时钟源 */
    periphclk_initstruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    periphclk_initstruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
    HAL_RCCEx_PeriphCLKConfig(&periphclk_initstruct);
    
    /* 配置中断优先级 */
    HAL_NVIC_SetPriority(RTC_Alarm_IRQn,2,2);
    HAL_NVIC_EnableIRQ(RTC_Alarm_IRQn);
}

/* 闹钟中断入口 */
void RTC_Alarm_IRQHandler(void)
{
    HAL_RTC_AlarmIRQHandler(&rtc_handle);
}

/* 闹钟回调函数 */
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
    printf("闹钟响了");
}

/* 读取备份寄存器 */
uint16_t rtc_read_bkr(uint8_t bkr_x)
{
    uint32_t data = 0;
    data = HAL_RTCEx_BKUPRead(&rtc_handle,bkr_x);
    return (uint16_t)data;
}

/* 写入备份寄存器 */
void rtc_write_bkr(uint8_t bkr_x,uint16_t data)
{
    HAL_RTCEx_BKUPWrite(&rtc_handle,bkr_x,data);
}

/* 获取当前时间并打印 */
void rtc_get_time(void)
{
    RTC_TimeTypeDef rtc_time = {0};
    RTC_DateTypeDef rtc_data = {0};
   
    /* 先读Time再读Date，解锁影子寄存器 */
    HAL_RTC_GetTime(&rtc_handle,&rtc_time,RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&rtc_handle,&rtc_data,RTC_FORMAT_BIN);
    
    printf("rtc time:%d-%02d-%02d %02d:%02d:%02d",rtc_data.Year+2000,rtc_data.Month,rtc_data.Date,
                                        rtc_time.Hours,rtc_time.Minutes,rtc_time.Seconds);
}

/* 设置RTC时间 */
void rtc_set_time(struct tm time_data)
{
    RTC_TimeTypeDef rtc_time = {0};
    RTC_DateTypeDef rtc_data = {0};
    
    /* 填充时间 */
    rtc_time.Hours = time_data.tm_hour;
    rtc_time.Minutes = time_data.tm_min;
    rtc_time.Seconds = time_data.tm_sec;
    HAL_RTC_SetTime(&rtc_handle,&rtc_time,RTC_FORMAT_BIN);
    
    /* 填充日期 (修正年份) */
    rtc_data.Year = time_data.tm_year - 2000;
    rtc_data.Month = time_data.tm_mon;
    rtc_data.Date = time_data.tm_mday;
    HAL_RTC_SetDate(&rtc_handle,&rtc_data,RTC_FORMAT_BIN);
    
    /* 等待同步 */
   while(!__HAL_RTC_ALARM_GET_FLAG(&rtc_handle,RTC_FLAG_RTOFF));
}

/* 设置RTC闹钟 */
void rtc_set_alarm(struct tm time_data)
{
    RTC_AlarmTypeDef    alarm_data_set = {0};

    /* 配置闹钟时间并开启中断 */
    alarm_data_set.Alarm = RTC_ALARM_A;
    alarm_data_set.AlarmTime.Hours      = time_data.tm_hour;
    alarm_data_set.AlarmTime.Minutes    = time_data.tm_min;
    alarm_data_set.AlarmTime.Seconds    = time_data.tm_sec;
    HAL_RTC_SetAlarm_IT(&rtc_handle,&alarm_data_set,RTC_FORMAT_BIN);
}
