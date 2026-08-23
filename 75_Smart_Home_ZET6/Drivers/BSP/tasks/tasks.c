#include "tasks.h"
#include "stdio.h"
#include "adc.h"
#include "beep.h"
#include "relay_fan.h"
#include "bluetooth.h"
#include "led.h"
#include "dht11.h"
#include "string.h"
#include "onenet.h"

uint32_t task1_cnt = 0;     // 任务1的计时计数器
uint32_t task2_cnt = 0;
uint32_t task3_cnt = 0;

uint8_t task1_flag = 0;     // 任务1的执行标志位
uint8_t task2_flag = 0;
uint8_t task3_flag = 0;

uint16_t adc_val[2] = {0};

uint8_t led_status = 0;
LedMode_t led_mode = MODE_AUTO;

uint8_t voice_cmd = 0;
uint8_t bt_cmd    = 0;

/**
 * @brief SysTick定时器中断服务函数
 * @note 用于实现任务的定时触发，通过计数器累加达到阈值后设置任务执行标志
 */
void timer_ISR(void)
{
    if(task1_cnt < 1)
    {
        task1_cnt++;
    }
    else
    {
        task1_flag = 1;
        task1_cnt = 0;
    }

    if(task2_cnt < 2)
    {
        task2_cnt++;
    }
    else
    {
        task2_flag = 1;
        task2_cnt = 0;
    }
    
    if(task3_cnt < 20)
    {
        task3_cnt++;
    }
    else
    {
        task3_flag = 1;
        task3_cnt = 0;
    }
}

void task_led_control(void)
{
    if(task1_flag == 1)
    {
        task1_flag = 0;
        
        // 1. 获取瞬时指令 (局部变量)
        uint8_t bt_cmd    = bluetooh_get_command();
        uint8_t voice_cmd = voice_get_cmd();
        uint8_t current_cmd = bt_cmd ? bt_cmd : voice_cmd;
        

        // 2. 模式抢占逻辑：如果是 2-5 号手动指令，立即更新模式状态
        if(current_cmd >= 2 && current_cmd <= 5)
        {
            led_mode = (bt_cmd) ? MODE_BT_CTRL : MODE_VOICE_CTRL;
        }

        // 3. 统一执行：无论 current_cmd 是几（包括 0），都进调度中心执行
        led_apply_action(current_cmd);

        // 4. 显式清理(局部变量可不用清理)
        bt_cmd = 0;
        voice_cmd = 0;
        current_cmd = 0;
    }
    else
    {
        return ;
    }
}

void task_gas_alarm(void)
{
    if(task2_flag == 1)
    {
        task2_flag = 0;
        
        get_adc_result(adc_val);
        float gas_val = 3.3 - (float)adc_val[0]/4096*3.3;
        if(gas_val > 1)
        {
            relay_fan_on();
            beep_alarm();
        }
        else
        {
            beep_off();
            relay_fan_off();
        }
    }
    else
    {
        return ;
    }
}

void task_temphum_upload(void)
{
    if(task3_flag == 1)
    {
        task3_flag = 0;
        
        uint8_t dht11_data[4];
        static uint8_t heart_beat_cnt = 0;
        float light_val = 0;
        uint8_t data_send_buf[512];
        
        dht11_read_data(dht11_data);
        light_val = (float)adc_val[1]/4096*3.3;
        memset(data_send_buf, 0, sizeof(data_send_buf));
        sprintf((char *)data_send_buf, "{\"id\":\"1720777789227\",\"version\":\"1.0\",\"params\":{\"CurrentTemperature\":{\"value\":%d.%d},\"RelativeHumidity\":{\"value\":%d.%d},\"LightLuxValue\":{\"value\":%.1f}}}"
        , dht11_data[2], dht11_data[3], dht11_data[0], dht11_data[1], light_val);
        mqtt_publish_data(POST_TOPIC, (char *)data_send_buf, 0);
        
        //心跳包
        heart_beat_cnt++;
        if(heart_beat_cnt >= 60)
        {
            mqtt_send_heart(); // 发送 C0 00 心跳报文
            heart_beat_cnt = 0;
            printf("Heartbeat Sent!\r\n");
        }
    }
    else
    {
        return ;
    }
}

/**
 * @brief 全能动作调度器
 * @param cmd: 指令号 (0-5)。0 代表无新指令，1-5 代表具体动作。
 */
void led_apply_action(uint8_t cmd)
{
    switch(cmd)
    {
        case 0: 
            /* 背景任务：如果没有新指令且处于自动模式，执行感光调节 */
            if(led_mode == MODE_AUTO)
            {
                get_adc_result(adc_val);
                // ADC 采样值转换公式：V = (ADC / 4096) * 3.3
                float lux_val = (float)adc_val[1] / 4096 * 3.3;
                led_brightness_auto(lux_val);
            }
            break;

        case 1: 
            led_mode = MODE_AUTO;           // 指令 1：重置为自动模式
            break;
            
        case 2: led_brightness_down();      break; // 指令 2：调暗
        case 3: led_brightness_up();        break; // 指令 3：调亮
        case 4: led_on();                   break; // 指令 4：开灯
        case 5: led_off();                  break; // 指令 5：关灯
        
        default: break;
    }
}
