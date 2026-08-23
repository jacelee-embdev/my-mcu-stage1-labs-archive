#include "delay.h"

/**
  * @brief  微秒级延时
  * @param  nus 延时时长，范围：0~233015
  * @retval 无
  */
void delay_us(uint32_t nus)
{
    uint32_t temp=0;
    //1.确定要数数多少个数
    SysTick->LOAD = 72 * nus;
    //2.清空当前计数
    SysTick->VAL = 0x00;
    //3.配置分频系数
    SysTick->CTRL |= 1<<2;
    //4.开启定时器
    SysTick->CTRL |= 1<<0;
    do
    {
        temp = SysTick->CTRL;
    }while((temp & 0x01) && (!(temp &(1<<16))));
    SysTick->CTRL &= ~(1<<0);   //关闭定时器
}

/**
  * @brief  毫秒级延时
  * @param  nms 延时时长，范围：0~4294967295
  * @retval 无
  */
void delay_ms(uint32_t nms)
{
    while(nms--)
        delay_us(1000);
}
 
/**
  * @brief  秒级延时
  * @param  ns 延时时长，范围：0~4294967295
  * @retval 无
  */
void delay_s(uint32_t ns)
{
    while(ns--)
        delay_ms(1000);
}

/**
  * @brief  重写HAL_Delay函数
  * @param  nms 延时时长，范围：0~4294967295
  * @retval 无
  */
void HAL_Delay(uint32_t nms)
{
    delay_ms(nms);
}
