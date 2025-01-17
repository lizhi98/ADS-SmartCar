/*
 * motor.h
 *
 *  Created on: 2024年11月23日
 *      Author: lizhi
 */

#ifndef CODE_MOTOR_H_
#define CODE_MOTOR_H_

#include<zf_driver_pwm.h>
#include "code/assert.h"

//对应主板上的电机信号2（需要修改一下）ATOM1_CH6_P02_6
#define MOTOR_LEFT_FORWARD_PWM_PIN          ATOM1_CH6_P02_6 	    //左电机的PWM引脚
#define MOTOR_LEFT_BACKWARD_PWM_PIN         ATOM1_CH4_P02_4 	    //左电机的PWM引脚
#define MOTOR_LEFT_FORWARD_PWM_STD_FREQ     17000           	    //左电机的PWM频率
#define MOTOR_LEFT_BACKWARD_PWM_STD_FREQ    17000           	    //左电机的PWM频率
#define MOTOR_LEFT_FORWARD_PWM_INIT_DUTY    0              	        //左电机的PWM初始占空比
#define MOTOR_LEFT_BACKWARD_PWM_INIT_DUTY   0                	    //左电机的PWM初始占空比

#define MOTOR_RIGHT_FORWARD_PWM_PIN         ATOM1_CH5_P02_5         //右电机的PWM引脚
#define MOTOR_RIGHT_BACKWARD_PWM_PIN        ATOM1_CH7_P02_7         //右电机的PWM引
#define MOTOR_RIGHT_FORWARD_PWM_STD_FREQ    17000                   //右电机的PWM频率
#define MOTOR_RIGHT_BACKWARD_PWM_STD_FREQ   17000                   //右电机的PWM频率
#define MOTOR_RIGHT_FORWARD_PWM_INIT_DUTY   0                    //右电机的PWM初始占空比
#define MOTOR_RIGHT_BACKWARD_PWM_INIT_DUTY  0                       //右电机的PWM初始占空比

#define MOTOR_PWM_DUTY_MAX                  (PWM_DUTY_MAX * 0.5)    //电机PWM占空比最大值
#define MOTOR_PWM_DUTY_MIN                  (0)                     //电机PWM占空比最小值，过小可能电机无法驱动[需要修改]

#define MOTOR_INIT_NORMAL_SPEED             80                    //电机直道初始速度
#define MOTOR_INIT_CURVE_SPEED              60                    //电机弯道初始速度

extern int motor_normal_speed;
extern int motor_curve_speed;

extern int 	motorLeftForwardPwmPresentDuty;
extern int 	motorLeftBackwardPwmPresentDuty;
extern int 	motorRightForwardPwmPresentDuty;
extern int 	motorRightBackwardPwmPresentDuty;

void motor_pwm_set_duty(pwm_channel_enum motor,int duty);
void motor_pwm_plus_duty(pwm_channel_enum motor,int16 plus);
void motor_pwm_record(pwm_channel_enum motor, int duty);
void motor_all_init(void);

void motor_start(void);
void motor_make_unpower(void);

#endif /* CODE_MOTOR_H_ */
