/*
 * pid.c
 *
 *  Created on: 2024年12月3日
 *      Author: lizhi
 */
#include"pid.h"

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
    uint32 duty = steerSetAngle * 8 + STEER_PWM_DUTY_MID;
    steer_set_duty(duty);
}
