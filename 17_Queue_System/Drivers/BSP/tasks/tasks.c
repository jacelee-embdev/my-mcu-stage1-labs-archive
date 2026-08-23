#include "sys.h"
#include "delay.h"
#include "tasks.h"
#include "led.h"
#include "beep.h"
#include "relay_gate.h"
#include "lcd1602.h"
#include "exti.h"
#include "stdio.h"

// 系统状态枚举定义：明确系统仅有的两种工作状态
enum
{
    PASS_STATE,
    WAIT_STATE
};

// 全局计时计数器：用于SysTick中断中累计时间，控制任务触发周期
uint32_t led1_task_cnt = 0;
uint32_t led2_task_cnt = 0;
uint32_t wait_cnt      = 0;
uint32_t passenger     = 0;

// 任务执行标志位：中断中置1，任务函数中检测到后执行对应逻辑并清0
uint8_t led1_task_flag      = 0;
uint8_t led2_task_flag      = 0;
uint8_t alarm_bee_task_flag = 0;

uint8_t state = PASS_STATE;     // 系统当前工作状态（默认初始化为通行状态）

char message[16] = {0};         // LCD1602显示字符串缓冲区（16字节适配屏幕宽度）

/**
 * @brief SysTick定时器中断服务函数
 * @details 系统定时核心，由硬件配置为1ms触发一次，负责：
 *          1. 按系统当前状态控制闸机开关状态
 *          2. 累计各硬件动作周期计数器，达到阈值时置位对应任务触发标志
 *          3. 等待状态下检测红外传感器状态，异常时触发报警标志
 *          4. 等待状态计时满5秒后，自动切换回通行状态并更新LCD显示
 */
void SysTick_ISR(void)
{
    // 系统处于通行状态时的处理逻辑
    if(state == PASS_STATE)
    {   
        Led2_OFF();
        relay_gate_ON();    //闸机打开
        //LED1以1s频率闪烁
        if(led1_task_cnt < 1000)
        {
            led1_task_cnt++;
        }
        else
        {
            led1_task_flag = 1;
            led1_task_cnt = 0;
        }
    }
    // 系统处于等待状态0时的处理逻辑
    else if(state == WAIT_STATE)
    {
        Led1_OFF();
        relay_gate_OFF();
        if(led2_task_cnt < 200)     //LED2以200ms频率闪烁
        {
            led2_task_cnt++;
        }
        else
        {
            led2_task_flag = 1;
            led2_task_cnt = 0;
        }

        // 读取红外传感器状态：若返回FALSE表示传感器被遮挡（有人强行通过）
        if(get_infrared_sensor_status() == FALSE)
        {
            alarm_bee_task_flag = 1;
        }
        
        //计时5s后,
        if(wait_cnt < 5000)
        {
            wait_cnt++;
        }
        else
        {
            wait_cnt = 0;
            //进入通行状态
            state = PASS_STATE;
            //LCD显示状态
            lcd1602_show_char_string(1,1,"PASS......");
        }
    }
}

/**
 * @brief LED1状态翻转任务函数
 * @details 多任务轮询中被周期性调用，功能：
 *          检测LED1任务触发标志，若标志为1则翻转LED1当前状态（亮→灭/灭→亮），
 *          执行完成后清0标志位，避免重复翻转。
 */
void led1_task(void)
{
    if(led1_task_flag == 1)
    {
        Led1Toggle();
        led1_task_flag = 0;
    }
    else
    {

        return ;
    }
}

/**
 * @brief LED2状态翻转任务函数
 * @details 多任务轮询中被周期性调用，功能：
 *          检测LED2任务触发标志，若标志为1则翻转LED2当前状态（亮→灭/灭→亮），
 *          执行完成后清0标志位，避免重复翻转。
 */
void led2_task(void)
{
    if(led2_task_flag == 1)
    {
        Led2Toggle();
        led2_task_flag = 0;
    }
    else
    {
        return ;
    }
}

/**
 * @brief LCD1602显示控制任务函数
 * @details 多任务轮询中被周期性调用，整合功能：
 *          1. 检测红外传感器通行触发信号（有人通过）
 *          2. 统计通行人数并格式化显示到LCD屏幕
 *          3. 当单轮通行人数达到5人时，切换系统到等待状态并更新LCD提示
 */
void lcd1602_task(void)
{
    //检测到有人通行
    if(get_infrared_sensor_flag() == TRUE && state == PASS_STATE)
    {
        //计数+1
        passenger ++;
        //LCD1602显示状态
        sprintf(message,"PASS...%02d/05",passenger);
        lcd1602_show_char_string(1,1,message);
    }
    // 当单轮通行人数达到或超过5人（最大允许通行人数）
    if(passenger >= 5)
    {
        //计数清零
        passenger = 0;
        //进入"禁止通行"状态
        state = WAIT_STATE;
        //LCD1602显示状态
        lcd1602_show_char_string(1,1,"WAIT........");
    }
}

/**
 * @brief 报警蜂鸣任务函数
 * @details 多任务轮询中被周期性调用，功能：
 *          检测报警蜂鸣触发标志，若标志为1则执行特定节奏的蜂鸣报警，
 *          报警完成后清0标志位，避免重复报警。
 *          报警节奏：400ms响→100ms停→200ms响→1500ms停→200ms响→100ms停
 */
void alarm_bee_task(void)
{
    if(alarm_bee_task_flag == 1)
    {
        Beep_ON();
        delay_ms(400);
        Beep_OFF();
        delay_ms(100);
        
        Beep_ON();
        delay_ms(200);
        Beep_OFF();
        delay_ms(100);
        
        Beep_ON();
        delay_ms(200);
        Beep_OFF();
        delay_ms(100);
        
        alarm_bee_task_flag = 0;
    }
    else
    {
        return ;
    }
}

