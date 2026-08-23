#include "delay.h"

/**
  * @brief  微秒级延时
  * @param  nus 延时时长，范围：0~233015
  * @retval 无
  */
void delay_us(uint32_t nus)
{
    uint32_t ticks;     
    uint32_t tcnt=0,told,tnow;
    uint32_t reload = SysTick->LOAD;            //"reload":SysTick 的重载值
    
    ticks = 72 * nus;                           //"ticks":延时nus微秒需要的总时钟周期数
    told=SysTick->VAL;                          //"told":延时开始时 SysTick 的初始计数值
    
    while(1)
    {
        tnow = SysTick->VAL;                    //"tnow":循环中实时读取的 SysTick 当前计数值
        if(tnow!=told)
        {
            if(tnow < told)
            {
                tcnt += told - tnow;           //"tcnt":累计已走过的时钟周期数  //tcnt=tcnt+( told - tnow);
            }
            else
            {
                tcnt += reload-(tnow - told);
            }
            
            told = tnow;                        // 更新基准值为当前计数
            if(tcnt >= ticks)                   // 若累计周期数达到总需求，退出延时
            {
                break;
            }
        }
    }
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
