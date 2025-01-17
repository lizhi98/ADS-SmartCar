/*
 * dirControl.c
 *
 *  Created on: 2024年11月23日
 *      Author: lizhi
 */
#include"motor.h"

int 	motorLeftForwardPwmPresentDuty;
int 	motorLeftBackwardPwmPresentDuty;
int 	motorRightForwardPwmPresentDuty;
int 	motorRightBackwardPwmPresentDuty;

// int16 	motorLeftSetSpeed;
// int16 	motorRightSetSpeed;
int motor_nomal_speed = MOTOR_INIT_NOMAL_SPEED;
int motor_curve_speed = MOTOR_INIT_CURVE_SPEED;

//==================基础函数=====================
/*
 * 函数功能： 初始化所有电机引脚PWM
 */
void motor_all_init(){

    pwm_init(MOTOR_LEFT_FORWARD_PWM_PIN,    MOTOR_LEFT_FORWARD_PWM_STD_FREQ,    MOTOR_LEFT_FORWARD_PWM_INIT_DUTY);
    pwm_init(MOTOR_LEFT_BACKWARD_PWM_PIN,   MOTOR_LEFT_BACKWARD_PWM_STD_FREQ,   MOTOR_LEFT_BACKWARD_PWM_INIT_DUTY);
    pwm_init(MOTOR_RIGHT_FORWARD_PWM_PIN,   MOTOR_RIGHT_FORWARD_PWM_STD_FREQ,   MOTOR_RIGHT_FORWARD_PWM_INIT_DUTY);
    pwm_init(MOTOR_RIGHT_BACKWARD_PWM_PIN,  MOTOR_RIGHT_BACKWARD_PWM_STD_FREQ,  MOTOR_RIGHT_BACKWARD_PWM_INIT_DUTY);
   	motorLeftForwardPwmPresentDuty      =   MOTOR_LEFT_FORWARD_PWM_INIT_DUTY;
   	motorLeftBackwardPwmPresentDuty     =   MOTOR_LEFT_BACKWARD_PWM_INIT_DUTY;
   	motorRightForwardPwmPresentDuty     =   MOTOR_RIGHT_FORWARD_PWM_INIT_DUTY;
   	motorRightBackwardPwmPresentDuty    =   MOTOR_RIGHT_BACKWARD_PWM_INIT_DUTY;
}
//!!!!!!!!!!!!!!!!!没有 正反转PWM同时设置的禁止保护!!!!!!!!!!!!
void motor_pwm_set_duty(pwm_channel_enum motor,int duty){
    if(duty == 0u){
        pwm_set_duty(motor, 0);
        motor_pwm_record(motor, 0);
        return;
    }
    if(duty > MOTOR_PWM_DUTY_MAX) {
        duty = MOTOR_PWM_DUTY_MAX;
    }else if(duty < MOTOR_PWM_DUTY_MIN){ 
        duty = MOTOR_PWM_DUTY_MIN;
    }
    pwm_set_duty(motor, duty);
    motor_pwm_record(motor, duty);
}
void motor_pwm_plus_duty(pwm_channel_enum motor,int16 plus){
    switch(motor){
        case MOTOR_LEFT_FORWARD_PWM_PIN :   motor_pwm_set_duty(MOTOR_LEFT_FORWARD_PWM_PIN,  (uint32)(motorLeftForwardPwmPresentDuty    + plus)  );break;
        case MOTOR_LEFT_BACKWARD_PWM_PIN :  motor_pwm_set_duty(MOTOR_LEFT_BACKWARD_PWM_PIN, (uint32)(motorLeftBackwardPwmPresentDuty   + plus)  );break;
        case MOTOR_RIGHT_FORWARD_PWM_PIN :  motor_pwm_set_duty(MOTOR_RIGHT_FORWARD_PWM_PIN, (uint32)(motorRightForwardPwmPresentDuty   + plus)  );break;
        case MOTOR_RIGHT_BACKWARD_PWM_PIN : motor_pwm_set_duty(MOTOR_RIGHT_BACKWARD_PWM_PIN,(uint32)(motorRightBackwardPwmPresentDuty  + plus)  );break;
        default:
            wrong();
            break;
    }
}
void motor_pwm_record(pwm_channel_enum motor, int duty){
    switch(motor){
        case MOTOR_LEFT_FORWARD_PWM_PIN :   motorLeftForwardPwmPresentDuty     = duty;break;
        case MOTOR_LEFT_BACKWARD_PWM_PIN :  motorLeftBackwardPwmPresentDuty    = duty;break;
        case MOTOR_RIGHT_FORWARD_PWM_PIN :  motorRightForwardPwmPresentDuty    = duty;break;
        case MOTOR_RIGHT_BACKWARD_PWM_PIN : motorRightBackwardPwmPresentDuty   = duty;break;
        default:
            wrong();
            break;
    }
}

//============高级函数===============
void motor_start(void){
    motor_pwm_set_duty(MOTOR_LEFT_FORWARD_PWM_PIN,  1000);
    motor_pwm_set_duty(MOTOR_RIGHT_FORWARD_PWM_PIN, 1000);
}
void motor_make_unpower(void){
    motor_pwm_set_duty(MOTOR_LEFT_FORWARD_PWM_PIN,  	0u);
    motor_pwm_set_duty(MOTOR_RIGHT_FORWARD_PWM_PIN, 	0u);
    motor_pwm_set_duty(MOTOR_LEFT_BACKWARD_PWM_PIN, 	0u);
    motor_pwm_set_duty(MOTOR_RIGHT_BACKWARD_PWM_PIN, 	0u);
}
