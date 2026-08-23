#include "sys.h"
#include "delay.h"
#include "uart1.h"
#include "led.h"
#include "beep.h"
#include "exti_vibrating_sensor.h"
#include "hcsr04.h"
#include "key.h"
#include "pwm_sg90.h" 
#include "trash_bin_ctrl_core.h"


int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    uart1_init(115200);
    LedInit();
    BeepInit();
    exti_vibrating_sensor();
    hcsr04_init();
    KeyInit();
    sg90_init();
    
    
    printf("Hello World!\n");
  
    uint8_t key_nub=0;
    while(1)
    {
        key_nub=KeyScan();
        // 触发条件：按键1按下 或 超声波检测距离<10cm（有人靠近）
        if(key_nub==1 || get_length_from_hcsr04() < 10)
        {
            open_trash_bin();// 执行开盖操作
            delay_ms(2000);// 保持开盖2秒
//            set_vibrate_flag(FALSE);
            set_trash_bin_status_flag(OPEN);// 更新垃圾桶状态为开盖
        }
        else
        {
            close_trash_bin();// 无触发条件，执行关盖操作
        }
         
        delay_ms(10);// 主循环短延时，降低CPU占用
    }
}
