#include "sys.h"
#include "delay.h"
#include "uart1.h"
#include "keyboard.h"
#include "beep.h"
#include "oled.h"
#include "relay_lock.h"
#include "w25q128.h"
#include "password.h"

int main(void)
{
    uint8_t key_last = 0;
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9);     /* 设置时钟, 72Mhz */
    uart1_init(115200);                 /* 初始化串口 */
    keyboard_init();
    BeepInit();
    oled_init();
    relay_lock_init();
    w25q128_init();
    password_init();
    printf("Hello Word!\r\n");
    
    password_check();
    
    
    while(1)
    {
        oled_show_input();
        key_last = password_get_input();
        
        if(key_last == POUND_KEY)
        {
            if(password_compare() == TRUE)
            {
                password_input_right_operate();
            }
            else
            {
                password_input_wrong_operate();
            }
        }
        else if(key_last == START_KEY)
        {
            oled_show_old();
            password_get_input();
            if(password_compare() == TRUE)
            {
                password_old_right_operate();
            }
            else
            {
                password_old_wrong_operate();
            }
        }
    }
}

/* =========================================================================
 * 后续优化方向
 * =========================================================================
*/
//1.字体"font"优化为灵活配置
//2.密码部分安全审核
//3.流程图重组(尤其是第一次下载程序后,建议给设定密码门部分单独拎出来做一个循环)
//4.继电器改为L298N驱动电机正反转
