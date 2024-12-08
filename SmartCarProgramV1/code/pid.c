/*
 * pid.c
 *
 *  Created on: 2024年12月3日
 *      Author: lizhi
 */
#include"pid.h"

struct MotorPIDConfig
left   =  {.KP = 1, .KI = 0, .KD = 0},
right  =  {.KP = 1, .KI = 0, .KD = 0};

struct SteerPIDConfig
steer  =  {.KP = 1, .KI = 0, .KD = 0};

//===========超简单开环PID===========

//让电机速度调整到设定值
void motor_make_same_with_seting(void){
    //左电机
    if (motorLeftSpeed == motorLeftSetSpeed || (abs(motorLeftSpeed - motorLeftSetSpeed) <= 100 && motorLeftSetSpeed != 0 )){
        return;
    }
    if(motorLeftSetSpeed > motorLeftSpeed){
        if(motorLeftBackwardPwmPresentDuty !=0){
            motor_pwm_set_duty(MOTOR_LEFT_BACKWARD_PWM_PIN, 0);
        }
        motor_pwm_plus_duty(MOTOR_LEFT_FORWARD_PWM_PIN, MOTOR_PWM_PLUS_PER_RUN);
    }else{
        if(motorLeftBackwardPwmPresentDuty !=0){
            motor_pwm_set_duty(MOTOR_LEFT_BACKWARD_PWM_PIN, 0);
        }
        motor_pwm_plus_duty(MOTOR_LEFT_FORWARD_PWM_PIN, -MOTOR_PWM_PLUS_PER_RUN);
    }
    //右电机
    if (motorRightSpeed == motorRightSetSpeed || (abs(motorRightSpeed - motorRightSetSpeed) <= 50 && motorRightSetSpeed != 0 )){
        return;
    }
    if(motorRightSetSpeed > motorRightSpeed ){
        if(motorRightBackwardPwmPresentDuty !=0){
            motor_pwm_set_duty(MOTOR_RIGHT_BACKWARD_PWM_PIN, 0);
        }
        motor_pwm_plus_duty(MOTOR_RIGHT_FORWARD_PWM_PIN, MOTOR_PWM_PLUS_PER_RUN);
    }else{
        if(motorRightBackwardPwmPresentDuty !=0){
            motor_pwm_set_duty(MOTOR_RIGHT_BACKWARD_PWM_PIN, 0);
        }
        motor_pwm_plus_duty(MOTOR_RIGHT_FORWARD_PWM_PIN, -MOTOR_PWM_PLUS_PER_RUN);
    }
}

//让舵机角度调整到设定值
void steer_make_same_with_setting(void){
    uint32 duty;
    if(element_type == Normal){
        duty = steerSetAngle * 1.5 + STEER_PWM_DUTY_MID;
    }else if(element_type == Curve){
        duty = -steerSetAngle * 1.5 + STEER_PWM_DUTY_MID;
    }

    steer_set_duty(duty);
}

void motor_pid_calc(struct MotorPIDConfig *pid){
    pid->error  = pid->target - pid->current;
    pid->out    = pid->KP  * pid->error  + pid->KI  * (pid->error + pid->lastError + pid->last2Error)  +  pid->KD * (pid->error - pid->lastError);
    pid->last2Error = pid->lastError;
    pid->lastError  = pid->error;
}
void steer_pid_calc(struct SteerPIDConfig *pid){
    pid->error  = pid->target - pid->current;
    pid->out    = STEER_PWM_DUTY_MID +pid->KP  * pid->error  + pid->KI  * (pid->error + pid->lastError + pid->last2Error)  +  pid->KD * (pid->error - pid->lastError);
    pid->last2Error = pid->lastError;
    pid->lastError  = pid->error;
}

void motor_pid_call(){
    motor_pid_calc(&left); motor_pid_calc(&right);
    motor_pwm_set_duty(MOTOR_LEFT_FORWARD_PWM_PIN,  left.out);
    motor_pwm_set_duty(MOTOR_RIGHT_FORWARD_PWM_PIN, right.out);
}

void steer_pid_call(){
    steer_pid_calc(&steer);
    steer_set_duty(steer.out);
}

