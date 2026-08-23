#include "control.h"
#include "mpu6050_exti.h"
#include "debug_usart.h"
#include "mpu6050.h"
#include "motor.h"
#include "encoder.h"
#include "bluetooth.h"

/* ================================================================================= */
/* [私有变量与句柄] 模块内部私有数据，严格限制作用域防污染                           */
/* ================================================================================= */
static float pitch, roll, yaw;                  // DMP解算后欧拉角数据缓存
static short gyro_x, gyro_y, gyro_z;            // 陀螺仪三轴原始角速度缓存

static float balance_kp         = 255.0f;       // 直立环比例系数 (源值推演: 255*19)
static float balance_kd         = 1.08f;        // 直立环微分系数 (源值推演: 1.08*19)

static float velocity_kp        = 90.0f;        // 速度环比例系数
static float velocity_ki        = 0.45f;        // 速度环积分系数

static float turn_kp            = -30.0f;       // 转向环比例系数
static float turn_kd            = -0.3f;        // 转向环微分系数

static int   balance_pwm        = 0;            // 直立环计算输出PWM
static int   velocity_pwm       = 0;            // 速度环计算输出PWM
static int   turn_pwm           = 0;            // 转向环计算输出PWM

static int   motor_l_pwm        = 0;            // 左电机最终输出PWM占空比
static int   motor_r_pwm        = 0;            // 右电机最终输出PWM占空比

static float target_speed       = 0.0f;         // 系统设定目标运行速度
static float turn_speed         = 0.0f;         // 系统设定目标转向角速度

static int   encoder_l          = 0;            // 左侧编码器行程增量
static int   encoder_r          = 0;            // 右侧编码器行程增量

static float mechanical_angle   = 0.0f;         // 车体零位机械偏置角
static uint8_t bluetooth_cmd    = 0;            // 蓝牙透传控制指令缓存

/* ---------------------------------------------------------------------------------- */
/* [逻辑处理层] 内部核心控制算法实现                                                 */
/* ---------------------------------------------------------------------------------- */

// 直立环PD控制计算：抵抗重力维持车体绝对机械平衡
static int balance_control_calc(float angle, float mechanical_balance, float gyro)
{
    float angle_error;
    int   balance_output;
    
    angle_error    = angle - mechanical_balance;
    balance_output = (balance_kp * angle_error) + (balance_kd * gyro);
    
    return balance_output;
}

// 速度环PI控制计算：跟随目标速度，并维持系统平移抗干扰稳定
static int velocity_control_calc(int encoder_l, int encoder_r, int target_speed)
{
    static float current_velocity  = 0.0f;
    static float encoder_error     = 0.0f;
    static float encoder_filter    = 0.0f;
    static float encoder_integral  = 0.0f;
    
    /* 阶段 1: 提取双轮速度偏差并进行低通滤波，平滑突变引起的抖动 */
    encoder_error   = (encoder_l + encoder_r) - target_speed;
    encoder_filter *= 0.8f;
    encoder_filter += encoder_error * 0.2f;
    
    /* 阶段 2: 速度偏差积分累加 */
    encoder_integral += encoder_filter;
    encoder_integral  = encoder_integral - target_speed;
    
    /* 阶段 3: 积分器抗饱和限幅，防止受阻堵转引发长时间的积分溢出失控 */
    if (encoder_integral > 10000.0f)  encoder_integral = 10000.0f;
    if (encoder_integral < -10000.0f) encoder_integral = -10000.0f;
    
    /* 阶段 4: 计算速度环输出 */
    current_velocity = (encoder_filter * velocity_kp) + (encoder_integral * velocity_ki);
    
    /* 阶段 5: 异常位姿保护，车体倾角过大(倒地)时强行清零积分器，防止扶起时剧烈前冲 */
    if (pitch < -40.0f || pitch > 40.0f)
    {
        encoder_integral = 0.0f;
    }
    
    return (int)current_velocity;
}

// 转向环PD控制计算：通过Z轴角速度反馈修正转向姿态
static int turn_control_calc(int gyro_z, int rc_cmd)
{
    int turn_output;
    
    /* * [动态参数调度] 
     * 无转向指令时：开启 Z 轴微分阻尼，抑制车体受扰动产生的原地自旋现象
     * 有转向指令时：关闭阻尼防对抗，恢复正常的转向比例系数以响应遥控输入
     */
    if (rc_cmd == 0)
    {
        turn_kd = -0.3f;
        turn_kp = -30.0f;    // 保持正常比例系数备用
    }
    else
    {
        turn_kd = 0.0f;      // 消除微分阻尼，提升转向灵敏度
        turn_kp = -30.0f;    // 修复：恢复转向比例系数响应控制权（原代码误置为 0.0f）
    }
    
    turn_output = (turn_kd * gyro_z) + (turn_kp * rc_cmd);
    
    return turn_output;
}

// 电机PWM输出占空比绝对值硬限幅保护
static void motor_pwm_limit(void)
{
    if (motor_l_pwm < -7000) motor_l_pwm = -7000;
    if (motor_l_pwm > 7000)  motor_l_pwm = 7000;
    if (motor_r_pwm < -7000) motor_r_pwm = -7000;
    if (motor_r_pwm > 7000)  motor_r_pwm = 7000;
}

/* ================================================================================= */
/* [应用层] 外部系统调用接口                                                         */
/* ================================================================================= */

// 接收蓝牙透传遥控指令并更新系统设定参数
void bluetooth_cmd_parse(void)
{
    bluetooth_cmd = bluetooth_get_command();
    
    switch (bluetooth_cmd)
    {
        case 0: // 待机复位
            target_speed = 0.0f;
            turn_speed   = 0.0f;
            break;
        case 1: // 加速指令
            target_speed += 1.0f;
            break;
        case 2: // 减速指令
            target_speed -= 1.0f;
            break;
        case 3: // 左转指令
            turn_speed -= 30.0f;
            break;
        case 4: // 右转指令
            turn_speed += 30.0f;
            break;
        default:
            break;
    }
}

// 控制系统核心主循环调度（置于文件尾部，符合调用树递进原则）
void control_task_loop(void)
{
    static uint8_t s_print_counter = 0;
    
    if (mpu6050_data_ready_flag)
    {
        mpu6050_data_ready_flag = 0; 
        
        /* [通信层] 提取蓝牙遥控透传指令并更新全局目标位姿态 */
        bluetooth_cmd_parse();
        
        /* 阶段 1: 采集传感器基准数据与执行器反馈数据 */
        mpu6050_dmp_get_data(&pitch, &roll, &yaw);
        mpu6050_get_gyroscope(&gyro_x, &gyro_y, &gyro_z);
        
        encoder_l = encoder_left_get_delta();
        encoder_r = encoder_right_get_delta();
        
        /* 阶段 2: 串级PID闭环独立解算 */
        balance_pwm  = balance_control_calc(pitch, mechanical_angle, gyro_y);
        velocity_pwm = velocity_control_calc(encoder_l, encoder_r, target_speed);
        turn_pwm     = turn_control_calc(gyro_z, turn_speed);
        
        /* 阶段 3: 多环输出混流控制 */
        motor_l_pwm = balance_pwm + velocity_pwm + turn_pwm;
        motor_r_pwm = balance_pwm + velocity_pwm - turn_pwm;
        
        /* 阶段 4: 占空比钳位限幅与底层物理驱动执行 */
        motor_pwm_limit();
        motor_set_speed(motor_l_pwm, motor_r_pwm);
        
        /* 阶段 5: 降频调试流输出，规避串口高频发送引发的时序污染 */
        if (s_print_counter >= MPU_PRINT_FREQ_DIV)
        {
            printf("balance_pwm:%d\r\n", balance_pwm);
            printf("pitch: %f roll:%f yaw:%f\r\n", pitch, roll, yaw);
            s_print_counter = 0;
        }
        s_print_counter++;
    }
}
