#include "sys.h"
#include "tasks.h"
#include "led.h"

uint32_t task1_cnt = 0;     // 任务1的计时计数器
uint32_t task2_cnt = 0;

uint8_t task1_flag = 0;     // 任务1的执行标志位
uint8_t task2_flag = 0;

/**
 * @brief SysTick定时器中断服务函数
 * @note 用于实现任务的定时触发，通过计数器累加达到阈值后设置任务执行标志
 */
void SysTick_ISR(void)
{
    if(task1_cnt < 1000)
    {
        task1_cnt++;
    }
    else
    {
        task1_flag = 1;
        task1_cnt = 0;
    }

    if(task2_cnt < 500)
    {
        task2_cnt++;
    }
    else
    {
        task2_flag = 1;
        task2_cnt = 0;
    }
}

/**
 * @brief 任务1执行函数：LED1状态翻转
 * @note 检测到任务1标志位时执行LED翻转，并清除标志
 */
void task1(void)
{
    if(task1_flag == 1)
    {
        Led1Toggle();
        task1_flag = 0;
    }
    else
    {
        return ;
    }
}

void task2(void)
{
    if(task2_flag == 1)
    {
        Led2Toggle();
        task2_flag = 0;
    }
    else
    {
        return ;
    }
}
