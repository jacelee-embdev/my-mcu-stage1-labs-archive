#include "sys.h"
#include "boot_animation.h"
#include "oled.h"
#include "delay.h"

// 反色显示控制 (1:开启, 0:关闭)
void oled_inverse_display(uint8_t enable)
{
    oled_write_command(enable ? 0xA7 : 0xA6);
}

// 绘制进度条
void oled_draw_progressbar(uint8_t x, uint8_t y, uint8_t width, uint8_t progress)
{
    uint8_t i;
    uint8_t fill_len = (width * progress) / 100;
    
    oled_set_cursor(x, y);
    for(i = 0; i < width; i++)
    {
        // 0xBD:填充纹理, 0x81:空边框
        oled_write_data(i < fill_len ? 0xBD : 0x81); 
    }
}

void oled_start_animation(void)
{
    uint8_t i, j;
    char *logo = "NBOS";
    uint8_t x_base = 40;
    
    oled_fill(0x00); 
    
    // --- 1. Logo故障入场 (放慢) ---
    oled_show_string(128, 2, "NBOS", 24); 
    
    for(i = 0; i < 4; i++)
    {
        // 随机闪现
        oled_show_char(x_base + i*12, 1 + (i%2), logo[i], 24); 
        delay_ms(100);   // 增加闪现停留
        oled_fill(0x00);
        
        // 逐字固定
        for(j = 0; j <= i; j++) 
        {
            oled_show_char(x_base + j*12, 2, logo[j], 24);
        }
        delay_ms(400);   // 每个字母停留时间大幅增加
    }
    
    // --- 2. 反色闪烁特效 (放慢) ---
    for(i = 0; i < 3; i++)
    {
        oled_inverse_display(1); 
        delay_ms(100);   // 闪烁间隔变长
        oled_inverse_display(0); 
        delay_ms(100);
    }
    delay_ms(500);       // 闪烁完后的缓冲时间

    // --- 3. 进度条加载 (模拟重负载) ---
    oled_show_string(35, 5, "SYSTEM BOOT", 12);
    
    for(i = 0; i <= 100; i += 5)
    {
        oled_draw_progressbar(14, 7, 100, i);
        
        // 模拟变速加载 (整体变慢)
        if(i < 60)      delay_ms(30);  // 前段匀速
        else if(i < 85) delay_ms(150); // 中段明显卡顿(模拟加载核心)
        else            delay_ms(20);  // 后段冲刺
    }
    
    // --- 4. 结束转场 (从容展示) ---
    delay_ms(800);
    oled_fill(0x00);
    
    oled_show_string(40, 2, "NBOS", 24);
    oled_show_string(52, 6, "- OK -", 16);
    delay_ms(2000);      // 最终画面停留2秒
    
    // 门帘关机特效
    oled_fill(0xAA); 
    delay_ms(150);
    oled_fill(0xFF); 
    delay_ms(150);
    oled_fill(0x00); 
}


// 显示数字 (x,y:坐标, num:数值, len:显示位数, size:字体大小)
// 比如 num=15, len=3 -> 显示 "015"
uint32_t oled_pow(uint8_t m, uint8_t n)
{
    uint32_t result = 1;
    while(n--) result *= m;
    return result;
}

void oled_show_num(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size)
{
    uint8_t t, temp;
    uint8_t enshow = 0;
    
    for(t = 0; t < len; t++)
    {
        temp = (num / oled_pow(10, len - t - 1)) % 10;
        
        // 如果想首位不显示0，把下面这行注释掉
        oled_show_char(x + (size / 2) * t, y, temp + '0', size);
    }
}


/* =========================================================================
 * 系统主桌面
 * Page占用: [0-1]状态栏, [2-3]CPU信息, [4]进度条, [5-6]温度
 * =========================================================================
 */
void oled_desktop_run(void)
{
    static uint8_t cpu_load = 0;
    static uint8_t temp_val = 35;
    static uint8_t tick_count = 0;
    static uint8_t time_min = 30;
    
    oled_fill(0x00); // 清屏
    
    // --- 1. 顶部状态栏 (Y=0, 占两页) ---
    oled_show_string(0, 0, "4G", 12);
    oled_show_string(40, 0, "12:", 12);
    oled_show_num(60, 0, time_min, 2, 12);
    oled_show_string(96, 0, "[BAT]", 12); 
    
    // --- 2. CPU信息 (Y=2, 占两页) ---
    oled_show_string(0, 2, "CPU Load:", 12);
    oled_show_num(64, 2, cpu_load, 3, 12);
    oled_show_string(88, 2, "%", 12);

    // --- 3. CPU进度条 (Y=4, 占一页) ---
    oled_draw_progressbar(0, 4, 100, cpu_load); 
    
    // --- 4. 温度信息 (Y=5, 占两页) ---
    oled_show_string(0, 5, "Core Temp:", 12);
    oled_show_num(70, 5, temp_val, 2, 12);
    oled_show_string(90, 5, "C", 12);

    // --- 数据模拟 ---
    tick_count++;
    if(tick_count % 2 == 0) 
    {
        cpu_load = (cpu_load + 7) % 95; 
    }
    
    if(tick_count > 20)
    {
        time_min++;
        if(time_min > 59) time_min = 0;
        tick_count = 0;
    }
}
