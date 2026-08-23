#include "motor.h"
#include "delay.h"

/* ================================================================================= */
/* [私有变量与句柄] 仅限本文件内部使用的状态或外设控制句柄                           */
/* ================================================================================= */
static TIM_HandleTypeDef pwm_handle = {0}; // 电机底层定时器控制句柄

/* ================================================================================= */
/* [私有底层驱动] 内部调用的硬件初始化逻辑与时序控制                                 */
/* ================================================================================= */

// 配置电机方向控制 GPIO (复用为推挽输出)
static void motor_port_init(void)
{
    GPIO_InitTypeDef gpio_initstruct = {0};
    
    MOTOR_DIR_CLK_ENABLE();
    
    gpio_initstruct.Pin   = MOTOR_L_BWD_PIN | MOTOR_L_FWD_PIN | MOTOR_R_BWD_PIN | MOTOR_R_FWD_PIN;
    gpio_initstruct.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio_initstruct.Pull  = GPIO_PULLUP;
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(MOTOR_DIR_PORT, &gpio_initstruct);
}

// 配置定时器 PWM 模式及其通道
static void motor_pwm_init(uint16_t arr, uint16_t psc) 
{
    TIM_OC_InitTypeDef pwm_config = {0}; 
    
    /* 阶段 1: 配置定时器基础时基 */
    pwm_handle.Instance           = MOTOR_PWM_TIM; 
    pwm_handle.Init.Prescaler     = psc; 
    pwm_handle.Init.Period        = arr; 
    pwm_handle.Init.CounterMode   = TIM_COUNTERMODE_UP; 
    HAL_TIM_PWM_Init(&pwm_handle);
    
    /* 阶段 2: 配置具体通道的 PWM 模式 */
    pwm_config.OCMode       = TIM_OCMODE_PWM1; 
    pwm_config.Pulse        = 0; 
    pwm_config.OCPolarity   = TIM_OCPOLARITY_HIGH; 
    HAL_TIM_PWM_ConfigChannel(&pwm_handle, &pwm_config, TIM_CHANNEL_1);
    HAL_TIM_PWM_ConfigChannel(&pwm_handle, &pwm_config, TIM_CHANNEL_4); 
    
    /* 阶段 3: 使能并启动定时器通道输出 */
    HAL_TIM_PWM_Start(&pwm_handle, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&pwm_handle, TIM_CHANNEL_4);
    
    // 针对 STM32F103C8T6 的高级定时器 TIM1，必须显式开启主输出使能
    if (MOTOR_PWM_TIM == TIM1)
    {
        __HAL_TIM_MOE_ENABLE(&pwm_handle);
    }
}

// 内部更新左电机 PWM 比较寄存器值
static void motor_set_left_speed(uint16_t compare_val) 
{
    __HAL_TIM_SET_COMPARE(&pwm_handle, TIM_CHANNEL_1, compare_val); 
}

// 内部更新右电机 PWM 比较寄存器值
static void motor_set_right_speed(uint16_t compare_val) 
{
    __HAL_TIM_SET_COMPARE(&pwm_handle, TIM_CHANNEL_4, compare_val); 
}

/* ================================================================================= */
/* [HAL库底层回调] 外设底层级初始化 (引脚复用挂载等)                                 */
/* ================================================================================= */
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim) 
{
    if(htim->Instance == MOTOR_PWM_TIM)
    {
        GPIO_InitTypeDef gpio_initstruct = {0};
        
        MOTOR_TIM_CLK_ENABLE();
        MOTOR_PWM_CLK_ENABLE();
        
        // 配置定时器输出引脚为复用推挽输出，移交硬件外设控制权
        gpio_initstruct.Pin   = MOTOR_PWM_L_PIN | MOTOR_PWM_R_PIN;
        gpio_initstruct.Mode  = GPIO_MODE_AF_PP;
        gpio_initstruct.Pull  = GPIO_PULLUP; 
        gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(MOTOR_PWM_PORT, &gpio_initstruct);
    }
}

/* ================================================================================= */
/* [应用层接口] 对外暴露的核心业务 API                                               */
/* ================================================================================= */

void motor_init(void)
{
    motor_port_init();
    motor_pwm_init(MOTOR_PWM_PERIOD, MOTOR_PWM_PRESCALER);
}

void motor_left_forward(void)
{
    HAL_GPIO_WritePin(MOTOR_DIR_PORT, MOTOR_L_BWD_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_DIR_PORT, MOTOR_L_FWD_PIN, GPIO_PIN_SET);
}

void motor_left_backward(void)
{
    HAL_GPIO_WritePin(MOTOR_DIR_PORT, MOTOR_L_BWD_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_DIR_PORT, MOTOR_L_FWD_PIN, GPIO_PIN_RESET);
}

void motor_left_stop(void)
{
    // 主动刹停逻辑：方向引脚置零，同时通过定时器将 PWM 占空比拉满至 100% 锁死电机
    HAL_GPIO_WritePin(MOTOR_DIR_PORT, MOTOR_L_BWD_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_DIR_PORT, MOTOR_L_FWD_PIN, GPIO_PIN_RESET);
    motor_set_left_speed(MOTOR_PWM_PERIOD + 1); 
}

void motor_right_forward(void)
{
    HAL_GPIO_WritePin(MOTOR_DIR_PORT, MOTOR_R_BWD_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_DIR_PORT, MOTOR_R_FWD_PIN, GPIO_PIN_SET);
}

void motor_right_backward(void)
{
    HAL_GPIO_WritePin(MOTOR_DIR_PORT, MOTOR_R_BWD_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_DIR_PORT, MOTOR_R_FWD_PIN, GPIO_PIN_RESET);
}

void motor_right_stop(void)
{
    // 主动刹停逻辑：方向引脚置零，同时通过定时器将 PWM 占空比拉满至 100% 锁死电机
    HAL_GPIO_WritePin(MOTOR_DIR_PORT, MOTOR_R_BWD_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_DIR_PORT, MOTOR_R_FWD_PIN, GPIO_PIN_RESET);
    motor_set_right_speed(MOTOR_PWM_PERIOD + 1); 
}

void motor_set_speed(int16_t speed_l, int16_t speed_r)
{
    /* 阶段 1: 解析左电机速度极性与占空比 */
    if(speed_l > 0)
    {
        motor_left_forward();
        motor_set_left_speed((uint16_t)speed_l);
    }
    else if(speed_l < 0)
    {
        motor_left_backward();
        motor_set_left_speed((uint16_t)(-speed_l));
    }
    else
    {
        motor_left_stop();
        // 注意：无需在此处重复清零 speed，stop 函数内部已接管了刹车所需的 100% 占空比
    }
    
    /* 阶段 2: 解析右电机速度极性与占空比 */
    if(speed_r > 0)
    {
        motor_right_forward();
        motor_set_right_speed((uint16_t)speed_r);
    }
    else if(speed_r < 0)
    {
        motor_right_backward();
        motor_set_right_speed((uint16_t)(-speed_r));
    }
    else
    {
        motor_right_stop();
    }
}

// 执行电机全功能逻辑测试序列 (包含独立、协同与转向测试)
void motor_test_sequence(void)
{
    /* [局部配置参数区] 定义测试档位与时间参数 */
    // 注意：这里的速度值是基于 ARR = 7199 设置的。
    const int16_t speed_low  = 2000;     // 低速档位
    const int16_t speed_mid  = 4500;     // 中速档位
    const int16_t speed_high = 7199;     // 高速档位 (满载)
    const int16_t speed_turn = 1800;     // 转向专用低速档位
    const uint32_t step_delay = 1500;    // 每个测试动作维持 1.5 秒
    const uint32_t stop_delay = 1000;    // 刹停后观察时间 1.0 秒

    /* ================================================================================= */
    /* 阶段 1: 左电机独立测试 (正反转与多段速度阶跃)                                     */
    /* ================================================================================= */
    // 左轮正转加速测试
    motor_set_speed(speed_low, 0);      delay_ms(step_delay);
    motor_set_speed(speed_mid, 0);      delay_ms(step_delay);
    motor_set_speed(speed_high, 0);     delay_ms(step_delay);
    motor_set_speed(0, 0);              delay_ms(stop_delay);  // 测试主动刹停

    // 左轮反转加速测试
    motor_set_speed(-speed_low, 0);     delay_ms(step_delay);
    motor_set_speed(-speed_mid, 0);     delay_ms(step_delay);
    motor_set_speed(-speed_high, 0);    delay_ms(step_delay);
    motor_set_speed(0, 0);              delay_ms(stop_delay);

    /* ================================================================================= */
    /* 阶段 2: 右电机独立测试 (正反转与多段速度阶跃)                                     */
    /* ================================================================================= */
    // 右轮正转加速测试
    motor_set_speed(0, speed_low);      delay_ms(step_delay);
    motor_set_speed(0, speed_mid);      delay_ms(step_delay);
    motor_set_speed(0, speed_high);     delay_ms(step_delay);
    motor_set_speed(0, 0);              delay_ms(stop_delay);  // 测试主动刹停

    // 右轮反转加速测试
    motor_set_speed(0, -speed_low);     delay_ms(step_delay);
    motor_set_speed(0, -speed_mid);     delay_ms(step_delay);
    motor_set_speed(0, -speed_high);    delay_ms(step_delay);
    motor_set_speed(0, 0);              delay_ms(stop_delay);

    /* ================================================================================= */
    /* 阶段 3: 双电机协同测试 (同步正反转)                                               */
    /* ================================================================================= */
    // 双轮同步正转加速
    motor_set_speed(speed_low, speed_low);   delay_ms(step_delay);
    motor_set_speed(speed_mid, speed_mid);   delay_ms(step_delay);
    motor_set_speed(speed_high, speed_high); delay_ms(step_delay);
    motor_set_speed(0, 0);                   delay_ms(stop_delay);

    // 双轮同步反转加速
    motor_set_speed(-speed_low, -speed_low);   delay_ms(step_delay);
    motor_set_speed(-speed_mid, -speed_mid);   delay_ms(step_delay);
    motor_set_speed(-speed_high, -speed_high); delay_ms(step_delay);
    motor_set_speed(0, 0);                     delay_ms(stop_delay);

    /* ================================================================================= */
    /* 阶段 4: 低速转向测试 (原地打转与差速转弯)                                         */
    /* ================================================================================= */
    // 1. 原地左转 (左轮反转，右轮正转)
    motor_set_speed(-speed_turn, speed_turn); 
    delay_ms(step_delay);
    motor_set_speed(0, 0);
    delay_ms(stop_delay);

    // 2. 原地右转 (左轮正转，右轮反转)
    motor_set_speed(speed_turn, -speed_turn); 
    delay_ms(step_delay);
    motor_set_speed(0, 0);
    delay_ms(stop_delay);

    // 3. 行进中左转弯 (左轮低速，右轮中速) - 差速转向
    motor_set_speed(speed_turn, speed_turn + 1500); 
    delay_ms(step_delay);
    motor_set_speed(0, 0);
    delay_ms(stop_delay);

    // 4. 行进中右转弯 (左轮中速，右轮低速) - 差速转向
    motor_set_speed(speed_turn + 1500, speed_turn); 
    delay_ms(step_delay);
    motor_set_speed(0, 0);
    delay_ms(stop_delay);
}
