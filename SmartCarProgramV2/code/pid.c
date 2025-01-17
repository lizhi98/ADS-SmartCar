#include "pid.h"
#include "motor.h"
#include "steer.h"
#include "encoder.h"
#include "image.h"
#include "zf_driver_pit.h"

PIDConfig    motor_pid_config;
PIDConfig    steer_pid_config;

PIDCalc      motor_left_pid_calc = { 0 };
PIDCalc      motor_right_pid_calc = { 0 };
PIDCalc      steer_pid_calc = { 0 };

void pid_init(void){
    motor_pid_config.KP = PID_MOTOR_INIT_KP;
    motor_pid_config.KI = PID_MOTOR_INIT_KI;
    // motor_pid_config.KD = PID_MOTOR_INIT_KD;
    steer_pid_config.KP = PID_STEER_INIT_KP;
    // steer_pid_config.KI = PID_STEER_INIT_KI;
    steer_pid_config.KD = PID_STEER_INIT_KD;
}

void pid_start_calc(void){
    pit_ms_init(PID_PIT_CH,PID_CALC_INTERVAL);
}
void pid_stop_calc_and_clear(void){
    pit_close(PID_PIT_CH);
    motor_left_pid_calc.integral = 0;
    motor_left_pid_calc.error = 0;
    motor_left_pid_calc.lastError = 0;
    motor_left_pid_calc.last2Error = 0;

    motor_right_pid_calc.integral = 0;
    motor_right_pid_calc.error = 0;
    motor_right_pid_calc.lastError = 0;
    motor_right_pid_calc.last2Error = 0;

    steer_pid_calc.integral = 0;
    steer_pid_calc.error = 0;
    steer_pid_calc.lastError = 0;
    steer_pid_calc.last2Error = 0;
}

void pid_set_motor_target(int target){
    motor_left_pid_calc.target  = 1.0 * target;
    motor_right_pid_calc.target = 1.0 * target;
}
void pid_set_steer_target(int duty){
    steer_pid_calc.target = 1.0 * duty;
}

int pid_calc(PIDConfig * pid_config , PIDCalc * pid_calc){
    // 存储旧的error
    pid_calc->last2Error = pid_calc->lastError;
    pid_calc->lastError = pid_calc->error;
    // 计算新的error
    pid_calc->error = pid_calc->target - pid_calc->current;
    // 计算out
    // p
    float pout = pid_config->KP * pid_calc->error;
    // i
    pid_calc->integral += pid_calc->error;
    // 积分限幅
    if (pid_calc->integral > PID_MOTOR_MAX_INTEGRAL) {
        pid_calc->integral = PID_MOTOR_MAX_INTEGRAL;
    }
    else if (pid_calc->integral < -PID_MOTOR_MAX_INTEGRAL) {
        pid_calc->integral = -PID_MOTOR_MAX_INTEGRAL;
    }
    float iout = pid_config->KI * pid_calc->integral;
    // d
    float dout = pid_config->KD * ( (pid_calc->error - pid_calc->lastError) + (pid_calc->lastError - pid_calc->last2Error) );

    pid_calc->out = (int)(pout + iout + dout);
    // 计算输出
    return (int)(pout + iout + dout);

}


int motor_calc(PIDConfig *pid_config , PIDCalc *pid_calc) {
    // 计算新的error
    pid_calc->error = pid_calc->target - pid_calc->current;
    // 计算out
    // p
    float pout = pid_config->KP * pid_calc->error;
    // i
    pid_calc->integral += pid_calc->error;
    // 积分限幅
    if (pid_calc->integral > PID_MOTOR_MAX_INTEGRAL) {
        pid_calc->integral = PID_MOTOR_MAX_INTEGRAL;
    }
    else if (pid_calc->integral < -PID_MOTOR_MAX_INTEGRAL) {
        pid_calc->integral = -PID_MOTOR_MAX_INTEGRAL;
    }
    float iout = pid_config->KI * pid_calc->integral;

    return pid_calc->out = (int) (pout + iout);
}


int steer_calc(PIDConfig *pid_config , PIDCalc *pd_calc){
    // 存储旧的error
    pd_calc->lastError = pd_calc->error;
    // 新的error
    pd_calc->error = search_result.offset;
    //pd_calc->error = 0 ;
    // 计算out
    // p
    float pout = pid_config->KP * pd_calc->error;
    // d
    float dout = pid_config->KD * ((pd_calc->error - pd_calc->lastError));

    return pd_calc->out = (int)(pout + dout);
}

