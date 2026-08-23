#include "rtc.h"
#include "stdio.h"

RTC_HandleTypeDef rtc_handle = {0};

/**
 * @brief 初始化RTC外设
 * @note  配置时钟源(LSE)、分频系数及开启备份域访问
 */
void rtc_init(void)
{
    /* 1. 开启电源和备份接口时钟，允许访问备份域 */
    __HAL_RCC_PWR_CLK_ENABLE();     //使能PWR时钟
    __HAL_RCC_BKP_CLK_ENABLE();     //使能BKP时钟
    HAL_PWR_EnableBkUpAccess();     //取消备份域保护
    
    /* 2. 配置RTC基本参数 */
    rtc_handle.Instance = RTC;      //RTC基地址
    rtc_handle.Init.AsynchPrediv = 32767;   //异步预分频(32.768KHz->1Hz)
    rtc_handle.Init.OutPut = RTC_OUTPUTSOURCE_NONE;     //禁止RTC引脚输出

    /* 3. 初始化RTC硬件 */
    HAL_RTC_Init(&rtc_handle);          
}

/**
 * @brief RTC底层MSP初始化回调
 * @param[in] hrtc RTC句柄指针
 */
void HAL_RTC_MspInit(RTC_HandleTypeDef *hrtc)
{
    
    RCC_OscInitTypeDef osc_initstruct = {0};
    RCC_PeriphCLKInitTypeDef periphclk_initstruct = {0};
    
    /* 1. 使能RTC外设时钟 */
    __HAL_RCC_RTC_ENABLE();
    
    /* 2. 配置LSE（外部低速晶振）作为RTC时钟源 */
    osc_initstruct.OscillatorType = RCC_OSCILLATORTYPE_LSE;
    osc_initstruct.LSEState = RCC_LSE_ON;
    osc_initstruct.PLL.PLLState = RCC_PLL_NONE;
    HAL_RCC_OscConfig(&osc_initstruct);

   /* 3. 关联RTC时钟源到外设 */
    periphclk_initstruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    periphclk_initstruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
    HAL_RCCEx_PeriphCLKConfig(&periphclk_initstruct);
}

/**
 * @brief 读取备份寄存器数值
 * @param[in] bkr_x 备份寄存器索引
 * @return 16位寄存器数据
 */
uint16_t rtc_read_bkr(uint8_t bkr_x)
{
    uint32_t data = 0;
    data = HAL_RTCEx_BKUPRead(&rtc_handle,bkr_x);   //读取备份寄存器数据
    return (uint16_t)data;
}

/**
 * @brief 向备份寄存器写入数据
 * @param[in] bkr_x 备份寄存器索引
 * @param[in] data  待写入的16位数据
 */
void rtc_write_bkr(uint8_t bkr_x,uint16_t data)
{
    HAL_RTCEx_BKUPWrite(&rtc_handle,bkr_x,data);    //向备份寄存器写入数据
}

/**
 * @brief 获取当前时间并通过串口打印
 * @note  包含年月日时分秒信息
 */
void rtc_get_time(void)
{
    RTC_TimeTypeDef rtc_time = {0};
    RTC_DateTypeDef rtc_data = {0};
   
    /* 必须按顺序读取：先读Time再读Date，以解锁影子寄存器 */
    HAL_RTC_GetTime(&rtc_handle,&rtc_time,RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&rtc_handle,&rtc_data,RTC_FORMAT_BIN);
    
    printf("rtc time:%d-%02d-%02d %02d:%02d:%02d",rtc_data.Year+2000,rtc_data.Month,rtc_data.Date,
                                        rtc_time.Hours,rtc_time.Minutes,rtc_time.Seconds);
}

/**
 * @brief 设置RTC时间
 * @param[in] time_data 标准时间结构体数据
 * @note  设置完成后等待寄存器同步
 */
void rtc_set_time(struct tm time_data)
{
    RTC_TimeTypeDef rtc_time = {0};
    RTC_DateTypeDef rtc_data = {0};
    
    /* 1. 填充时间结构体 (tm结构体转RTC格式) */
    rtc_time.Hours = time_data.tm_hour;
    rtc_time.Minutes = time_data.tm_min;
    rtc_time.Seconds = time_data.tm_sec;
    HAL_RTC_SetTime(&rtc_handle,&rtc_time,RTC_FORMAT_BIN);
    
    /* 2. 填充日期结构体 (年份需修正，tm_year是自1900起的年份) */
    rtc_data.Year = time_data.tm_year - 2000;
    rtc_data.Month = time_data.tm_mon;
    rtc_data.Date = time_data.tm_mday;
    HAL_RTC_SetDate(&rtc_handle,&rtc_data,RTC_FORMAT_BIN);
    
    /* 3. 等待RTC寄存器写操作完成 (检查RTOFF位) */
    /* F1系列在写操作后必须等待，确保数据同步到RTC内核 */
   while(!__HAL_RTC_ALARM_GET_FLAG(&rtc_handle,RTC_FLAG_RTOFF));
}
