#include "sys.h"
#include "delay.h"
#include "uart1.h"
#include "oled.h"
#include "boot_animation.h"

extern const unsigned char shuai_data[];
int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    uart1_init(115200);
    oled_init();
    printf("Hello World!\n");
    
    oled_fill(0x00);
/* =========================================================================
 * 测试
 * =========================================================================
 */
    //英文字母,数字及标点测试
    oled_show_string(36,3,"LZQ1?",24);
    delay_ms(1000);
    oled_fill(0x00);
    
    //汉字测试(front.h中仅包含"李知秋",自己按需添加)
    uint8_t i;
    for(i = 0;i<3;i++)
    {
        oled_show_Chinese(i*24+24,3,i,24);
    }
    delay_ms(1000);
    oled_fill(0x00);
    
    //图片测试(front.h中仅包含"帅",自己按需添加)
    oled_show_imge(0,0,128,8,(unsigned char*)shuai_data);
    delay_ms(1000);
    
    
/* =========================================================================
* 开机
 * =========================================================================
 */
    //开机动画
    oled_fill(0x00);
    delay_ms(1000);
    oled_start_animation(); 
    
    //桌面
    while(1)
    { 
        // 运行桌面逻辑
        oled_desktop_run();
        
        // 控制刷新率 (每500ms刷新一次，避免屏幕闪烁太快)
        delay_ms(1000);
    }
}
