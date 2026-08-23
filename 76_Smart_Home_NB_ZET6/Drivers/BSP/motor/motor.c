#include "motor.h"

// 定时器句柄声明
TIM_HandleTypeDef htim8;

/**
 * @brief  TIM8 PWM底层引脚初始化 (MSP)
 * @note   被HAL_TIM_PWM_Init调用，配置GPIO复用功能
 */
//void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
//{
//    GPIO_InitTypeDef gpio_config = {0};

//    if(htim->Instance == MOTOR_TIM_INSTANCE)
//    {
//        // 1. 开启时钟
//        MOTOR_TIM_CLK_ENABLE();
//        LOCK_PWM_CLK_ENABLE(); // PC时钟
//        FAN_PWM_CLK_ENABLE();  // PC时钟 (重复开启无影响)
//        
//        // 2. 配置锁控电机 PWM 引脚 (PC7) -> 复用推挽
//        gpio_config.Pin = LOCK_PWM_PIN;
//        gpio_config.Mode = GPIO_MODE_AF_PP;
//        gpio_config.Pull = GPIO_NOPULL;
//        gpio_config.Speed = GPIO_SPEED_FREQ_HIGH;
//        HAL_GPIO_Init(LOCK_PWM_PORT, &gpio_config);

//        // 3. 配置风扇电机 PWM 引脚 (PC8) -> 复用推挽
//        gpio_config.Pin = FAN_PWM_PIN;
//        HAL_GPIO_Init(FAN_PWM_PORT, &gpio_config);
//    }
//}

/**
 * @brief  初始化所有电机相关的GPIO (方向控制引脚)
 */
static void motor_gpio_config(void)
{
    GPIO_InitTypeDef gpio_config = {0};

    // 开启 GPIOB 时钟
    LOCK_DIR_CLK_ENABLE();
    FAN_DIR_CLK_ENABLE();
    
    __HAL_RCC_AFIO_CLK_ENABLE();
    __HAL_AFIO_REMAP_SWJ_NOJTAG();

    // 通用配置参数
    gpio_config.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_config.Pull = GPIO_PULLUP;
    gpio_config.Speed = GPIO_SPEED_FREQ_HIGH;

    // 1. 锁控电机方向引脚 (PB8, PB9)
    gpio_config.Pin = LOCK_IN1_PIN | LOCK_IN2_PIN;
    HAL_GPIO_Init(LOCK_DIR_PORT, &gpio_config);

    // 2. 风扇电机方向引脚 (PB6, PB7)
    gpio_config.Pin = FAN_IN3_PIN | FAN_IN4_PIN;
    HAL_GPIO_Init(FAN_DIR_PORT, &gpio_config);

    // 默认停止 (全部拉低)
    HAL_GPIO_WritePin(LOCK_DIR_PORT, LOCK_IN1_PIN | LOCK_IN2_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(FAN_DIR_PORT, FAN_IN3_PIN | FAN_IN4_PIN, GPIO_PIN_RESET);
}

/**
 * @brief  初始化定时器PWM功能 (TIM8)
 */
static void motor_pwm_config(void)
{
    TIM_OC_InitTypeDef pwm_config = {0};

    // 1. 定时器基础配置
    // 假设系统时钟72MHz。PSC=71 -> 1MHz计数频率。ARR=999 -> 1kHz PWM频率。
    htim8.Instance = MOTOR_TIM_INSTANCE;
    htim8.Init.Prescaler = 72 - 1;
    htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim8.Init.Period = 1000 - 1; 
    htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim8.Init.RepetitionCounter = 0;
    HAL_TIM_PWM_Init(&htim8);

    // 2. PWM通道配置
    pwm_config.OCMode = TIM_OCMODE_PWM1;
    pwm_config.Pulse = 0; // 初始占空比0
    pwm_config.OCPolarity = TIM_OCPOLARITY_HIGH;
    pwm_config.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    pwm_config.OCFastMode = TIM_OCFAST_DISABLE;
    pwm_config.OCIdleState = TIM_OCIDLESTATE_RESET;
    pwm_config.OCNIdleState = TIM_OCNIDLESTATE_RESET;

    // 配置锁控电机通道 (CH2)
    HAL_TIM_PWM_ConfigChannel(&htim8, &pwm_config, LOCK_PWM_CHANNEL);
    
    // 配置风扇电机通道 (CH3)
    HAL_TIM_PWM_ConfigChannel(&htim8, &pwm_config, FAN_PWM_CHANNEL);

    // 3. 开启PWM输出
    HAL_TIM_PWM_Start(&htim8, LOCK_PWM_CHANNEL);
    HAL_TIM_PWM_Start(&htim8, FAN_PWM_CHANNEL);

    // 4. 重要：高级定时器必须使能主输出 (MOE位)
    __HAL_TIM_MOE_ENABLE(&htim8);
}

/**
 * @brief  电机模块总初始化入口
 */
void motor_init(void)
{
    motor_gpio_config();
    motor_pwm_config();
}

/**
 * @brief  锁控电机控制逻辑
 * @param  state: MOTOR_STOP, MOTOR_FWD, MOTOR_REV
 * @param  speed: PWM占空比 (0~999)
 */
void lock_motor_set(motor_state_t state, uint16_t speed)
{
    // 限制最大PWM值
    if(speed > 999) speed = 999;

    // 设置方向
    switch(state)
    {
        case MOTOR_FWD:
            HAL_GPIO_WritePin(LOCK_DIR_PORT, LOCK_IN1_PIN, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LOCK_DIR_PORT, LOCK_IN2_PIN, GPIO_PIN_RESET);
            break;
        case MOTOR_REV:
            HAL_GPIO_WritePin(LOCK_DIR_PORT, LOCK_IN1_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LOCK_DIR_PORT, LOCK_IN2_PIN, GPIO_PIN_SET);
            break;
        case MOTOR_STOP:
        default:
            HAL_GPIO_WritePin(LOCK_DIR_PORT, LOCK_IN1_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LOCK_DIR_PORT, LOCK_IN2_PIN, GPIO_PIN_RESET);
            speed = 0; // 强制关断PWM
            break;
    }

    // 设置PWM占空比
    __HAL_TIM_SET_COMPARE(&htim8, LOCK_PWM_CHANNEL, speed);
}

/**
 * @brief  锁控电机立即停止
 */
void lock_motor_stop(void)
{
    lock_motor_set(MOTOR_STOP, 0);
}

/**
 * @brief  风扇电机控制逻辑
 * @param  state: MOTOR_STOP, MOTOR_FWD, MOTOR_REV
 * @param  speed: PWM占空比 (0~999)
 */
void fan_motor_set(motor_state_t state, uint16_t speed)
{
    // 限制最大PWM值
    if(speed > 999) speed = 999;

    // 设置方向
    switch(state)
    {
        case MOTOR_FWD:
            HAL_GPIO_WritePin(FAN_DIR_PORT, FAN_IN3_PIN, GPIO_PIN_SET);
            HAL_GPIO_WritePin(FAN_DIR_PORT, FAN_IN4_PIN, GPIO_PIN_RESET);
            break;
        case MOTOR_REV:
            HAL_GPIO_WritePin(FAN_DIR_PORT, FAN_IN3_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(FAN_DIR_PORT, FAN_IN4_PIN, GPIO_PIN_SET);
            break;
        case MOTOR_STOP:
        default:
            HAL_GPIO_WritePin(FAN_DIR_PORT, FAN_IN3_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(FAN_DIR_PORT, FAN_IN4_PIN, GPIO_PIN_RESET);
            speed = 0; // 强制关断PWM
            break;
    }

    // 设置PWM占空比
    __HAL_TIM_SET_COMPARE(&htim8, FAN_PWM_CHANNEL, speed);
}

/**
 * @brief  风扇电机立即停止
 */
void fan_motor_stop(void)
{
    fan_motor_set(MOTOR_STOP, 0);
}

/**
 * @brief  开门函数
 * @note   控制锁控电机正转，持续 10 秒后自动停止
 */
void door_open(void)
{
    // 开启正转，速度设定为 800 (参考测试函数值)
    lock_motor_set(MOTOR_FWD, 800); 
    
    // 延时 10,000 毫秒 (10秒)
    HAL_Delay(2000);
    
    // 停止电机
    lock_motor_stop();
}

/**
 * @brief  关门函数 (上锁)
 * @note   控制锁控电机反转，持续 10 秒后自动停止
 */
void door_close(void)
{
    // 开启反转，速度设定为 800
    lock_motor_set(MOTOR_REV, 800);
    
    // 延时 10,000 毫秒 (10秒)
    HAL_Delay(2000);
    
    // 停止电机
    lock_motor_stop();
}


/**
 * @brief  风扇电机持续运行函数
 * @note   设定为 40% 占空比持续正转。
 * 计算方法：ARR = 999，则 40% 约为 400。
 */
void fan_run_80pct(void)
{
    // 持续正转，不带延时
    fan_motor_set(MOTOR_FWD, 800); 
}


/**
 * @brief 电机模块综合测试函数
 * @note  循环测试锁控电机与风扇电机的方向控制与PWM调速功能
 * @note  速度范围参考之前配置的 ARR = 999，有效值为 0 ~ 999
 */
void motor_total_test(void)
{
    // --- 1. 初始状态归零 ---
    // 确保上电或重置后处于静止状态
    lock_motor_stop();
    fan_motor_stop();
    HAL_Delay(1000); 

    // --- 2. 锁控电机 (Lock Motor) 专项测试 ---
    // 正转：模拟开锁动作，中高流速 (速度 800)
    lock_motor_set(MOTOR_FWD, 800);
    HAL_Delay(2000);
    
    // 反转：模拟闭锁复位，中速 (速度 500)
    lock_motor_set(MOTOR_REV, 500);
    HAL_Delay(2000);
    
    // 停止锁控电机
    lock_motor_stop();
    HAL_Delay(1000);

    // --- 3. 风扇电机 (Fan Motor) 专项测试 ---
    // 低速启动：模拟微风模式 (速度 300)
    fan_motor_set(MOTOR_FWD, 300);
    HAL_Delay(2000);
    
    // 加速测试：切换至强风模式 (速度 999)
    fan_motor_set(MOTOR_FWD, 999);
    HAL_Delay(3000);
    
    // 换向测试：模拟反向抽风或自清洁 (速度 800)
    fan_motor_set(MOTOR_REV, 800);
    HAL_Delay(2000);
    
    // 停止风扇电机
    fan_motor_stop();
    HAL_Delay(1000);

    // --- 4. 复合联动测试 ---
    // 锁控电机正转(600) 的同时，风扇电机开启中速(600)
    lock_motor_set(MOTOR_FWD, 600);
    fan_motor_set(MOTOR_FWD, 600);
    HAL_Delay(3000);

    // --- 5. 测试结束，全系统停止 ---
    lock_motor_stop();
    fan_motor_stop();
    HAL_Delay(500);
}

