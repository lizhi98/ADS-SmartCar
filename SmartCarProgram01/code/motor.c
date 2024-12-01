/*
 * dirControl.c
 *
 *  Created on: 2024年11月23日
 *      Author: lizhi
 */
#include"motor.h"

/*
 * 函数功能： 初始化所有电机引脚PWM
 */
void motor_all_init(){

}
void motor_all_pwm_set_duty(uint32 duty){
    if(duty > MOTOR_PWM_DUTY_MAX){
        pwm_set_duty(MOTOR_LEFT_FORWARD_PWM_PIN, MOTOR_PWM_DUTY_MAX);
    }else if(duty < MOTOR_PWM_DUTY_MIN){
        pwm_set_duty(MOTOR_LEFT_FORWARD_PWM_PIN, MOTOR_PWM_DUTY_MIN);
    }
    pwm_set_duty(MOTOR_LEFT_FORWARD_PWM_PIN, duty);
}
void motor_left_pwm_set_duty(uint32 duty);
void motor_right_pwm_set_duty(uint32 duty);
void motor_all_close(void);
