#include "tasks.h"
#include "stdio.h"
#include "adc.h"
#include "beep.h"
#include "bluetooth.h"
#include "voice.h"
#include "led.h"
#include "dht11.h"
#include "string.h"
#include "onenet.h"
#include "motor.h"

// --- 计数器变量 ---
uint32_t task1_cnt = 0;
uint32_t task2_cnt = 0;
uint32_t task3_cnt = 0;
// task4, task5 不需要计数器了，因为它们是“指令驱动”的，有指令就动，没指令不动

// --- 标志位变量 ---
uint8_t task1_flag = 0;
uint8_t task2_flag = 0;
uint8_t task3_flag = 0;

// --- 全局状态变量 ---
uint16_t adc_val[2] = {0};
LedMode_t led_mode = MODE_AUTO; // 默认为自动模式
uint8_t fan_manual_on = 0;      // 关键：风扇手动开启标记 (0:关, 1:开)


/**
 * @brief 定时器中断服务函数 (系统心跳 10ms)
 * @note  解决了“反应慢”的问题：一旦有指令，立即强制执行，不等待计数器
 */
void timer_ISR(void)
{
    // ==========================================
    // 1. 周期性任务计数 (自动逻辑仍需定时)
    // ==========================================
    
    // Task 1 (LED自动调节): 100ms 一次，避免闪烁
    if(task1_cnt < 10) task1_cnt++;
    else {
        task1_flag = 1;
        task1_cnt = 0;
    }

    // Task 2 (燃气报警): 100ms 一次
    if(task2_cnt < 10) task2_cnt++;
    else {
        task2_flag = 1;
        task2_cnt = 0;
    }
    
    // Task 3 (上传): 降频处理，例如 1秒(100*10ms)一次，防止发太快堵塞
    if(task3_cnt < 100) task3_cnt++;
    else {
        task3_flag = 1;
        task3_cnt = 0;
    }

    // ==========================================
    // 2. 指令获取与分发 (解决指令丢失的核心)
    // ==========================================
    
    // 统一读取一次，防止被某个任务单独读走后清零
    uint8_t bt_raw = bluetooh_get_command();
    uint8_t vo_raw = voice_get_cmd();
    uint8_t current_cmd = bt_raw ? bt_raw : vo_raw; // 优先取非0的指令

    // ==========================================
    // 3. 任务调度
    // ==========================================
    
    // 无论 task_flag 是否为 1，只要有指令(current_cmd != 0)，就立即传给任务处理
    
    task1_led_control(current_cmd); // 处理 1-5 号指令 + 自动感光
    task2_gas_alarm();              // 处理燃气 (无指令交互)
    task3_temphum_upload();         // 处理上传 (无指令交互)
    task4_fan_ctrl(current_cmd);    // 处理 8-9 号指令
    task5_lock_ctrl(current_cmd);   // 处理 6-7 号指令
}

/**
 * @brief Task 1: LED 灯光控制
 * @note  同时负责处理指令(立即)和自动感光(定时)
 */
void task1_led_control(uint8_t cmd)
{
    // Part A: 优先处理指令 (如果有)
    if(cmd != 0)
    {
        switch(cmd)
        {
            case 1: led_mode = MODE_AUTO;    printf("LED: Auto Mode\r\n"); break;
            case 2: led_mode = MODE_BT_CTRL; led_brightness_down(); break;
            case 3: led_mode = MODE_BT_CTRL; led_brightness_up();   break;
            case 4: led_mode = MODE_BT_CTRL; led_on();  break;
            case 5: led_mode = MODE_BT_CTRL; led_off(); break;
            default: break; // 不是我的指令我就不管
        }
    }
    
    // Part B: 处理周期性自动感光 (仅在自动模式 + 时间到了才执行)
    if(task1_flag == 1)
    {
        task1_flag = 0; // 清除时间标志
        
        if(led_mode == MODE_AUTO)
        {
            get_adc_result(adc_val);
            float lux_val = (float)adc_val[1] / 4096 * 3.3;
            led_brightness_auto(lux_val);
        }
    }
}

/**
 * @brief Task 2: 燃气报警与安全逻辑
 * @note  解决了“风扇自动停”的问题
 */
void task2_gas_alarm(void)
{
    // 只在时间片到达时检测，没必要太快
    if(task2_flag == 1)
    {
        task2_flag = 0;
        get_adc_result(adc_val);
        float gas_val = 3.3 - (float)adc_val[0]/4096*3.3;

        if(gas_val > 1.0f) // 危险：燃气超标
        {
            fan_run_80pct(); // 无论手动自动，强制开启排风
            beep_alarm();
        }
        else // 安全状态
        {
            beep_off();
            
            // --- 核心修复逻辑 ---
            // 只有在“没有手动开启”且“燃气正常”时，才允许关风扇
            // 这样如果你用语音开了风扇，这里就不会把它强制关掉
            if(fan_manual_on == 0) 
            {
                fan_motor_stop();
            }
        }
    }
}

/**
 * @brief Task 3: 温湿度数据上传
 */
void task3_temphum_upload(void)
{
    if(task3_flag == 1)
    {
        task3_flag = 0;
        
        uint8_t dht11_data[4];
        static uint8_t heart_beat_cnt = 0;
        float light_val = 0;
        uint8_t data_send_buf[256]; // 512可能栈溢出，改小一点更安全
        
        dht11_read_data(dht11_data); // 直接调用读取数据，不判断返回值
        // 读取并校验
        if(dht11_data[0] != 0 || dht11_data[2] != 0) // 假设返回0表示成功，根据你的dht11.c调整
        {
             light_val = (float)adc_val[1]/4096*3.3;
             memset(data_send_buf, 0, sizeof(data_send_buf));
             
             sprintf((char *)data_send_buf, "{\"id\":\"18402259874\",\"version\":\"1.0\",\"params\":{\"CurrentTemperature\":{\"value\":%d.%d},\"RelativeHumidity\":{\"value\":%d.%d},\"LightLuxValue\":{\"value\":%.1f}}}"
             , dht11_data[2], dht11_data[3], dht11_data[0], dht11_data[1], light_val);
             
             mqtt_publish_data(POST_TOPIC, (char *)data_send_buf, 0);
        }
        
        // 心跳包逻辑 (60 * task3周期)
        heart_beat_cnt++;
        if(heart_beat_cnt >= 60)
        {
            mqtt_send_heart(); 
            heart_beat_cnt = 0;
        }
    }
}

/**
 * @brief Task 4: 风扇控制任务 (修正版)
 * @param cmd: 接收 8(开) 和 9(关)
 */
void task4_fan_ctrl(uint8_t cmd)
{
    // 风扇任务不需要等待 flag，有指令直接动
    
    if(cmd == 8) // 语音/蓝牙：打开风扇
    {
        fan_manual_on = 1; // 标记：这是主人手动开的，Task2别随便关
        fan_run_80pct();
        printf("Fan: Manual ON\r\n");
    }
    else if(cmd == 9) // 语音/蓝牙：关闭风扇
    {
        fan_manual_on = 0; // 标记：手动结束，恢复自动控制
        fan_motor_stop();
        printf("Fan: Manual OFF\r\n");
    }
}

/**
 * @brief Task 5: 门锁控制任务 (修正版)
 * @param cmd: 接收 6(开) 和 7(关)
 */
void task5_lock_ctrl(uint8_t cmd)
{
    // 门锁任务也不需要等待 flag，有指令直接动
    
    if(cmd == 6) // 开门
    {
        door_open();
        printf("Door: Open\r\n");
    }
    else if(cmd == 7) // 关门
    {
        door_close();
        printf("Door: Close\r\n");
    }
}
