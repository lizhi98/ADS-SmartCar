/*
 * motor.h
 *
 *  Created on: 2024年11月23日
 *      Author: lizhi
 */

#ifndef CODE_MOTOR_H_
#define CODE_MOTOR_H_

#include<zf_driver_pwm.h>

//对应主板上的电机信号2（需要修改一下）
#define MOTOR_LEFT_FORWARD_PWM_PIN          ATOM1_CH4_P02_4 	    //左电机的PWM引脚
#define MOTOR_LEFT_BACKWARD_PWM_PIN         ATOM1_CH6_P02_6 	    //左电机的PWM引脚
#define MOTOR_LEFT_FORWARD_PWM_STD_FREQ     17000           	    //左电机的PWM频率
#define MOTOR_LEFT_BACKWARD_PWM_STD_FREQ    17000           	    //左电机的PWM频率
#define MOTOR_LEFT_PWM_PIN1_INIT_DUTY       5000              	    //左电机的PWM初始占空比
#define MOTOR_LEFT_PWM_PIN2_INIT_DUTY       5000                	//左电机的PWM初始占空比

#define MOTOR_RIGHT_PWM_PIN1                ATOM1_CH5_P02_5     	//右电机的PWM引脚
#define MOTOR_RIGHT_PWM_PIN2                ATOM1_CH7_P02_7     	//右左电机的PWM引脚
#define MOTOR_RIGHT_PWM_PIN1_STD_FREQ       17000            	    //右左电机的PWM频率
#define MOTOR_RIGHT_PWM_PIN2_STD_FREQ       17000           t55        //右电机的PWM频率
#define MOTOR_RIGHT_PWM_PIN1_INIT_DUTY      5000                    //右电机的PWM初始占空比
#define MOTOR_RIGHT_PWM_PIN2_INIT_DUTY      5000                    //右电机的PWM初始占空比

#define MOTOR_PWM_DUTY_MAX                  (PWM_DUTY_MAX * 0.6)    //电机PWM占空比最大值
#define MOTOR_PWM_DUTY_MIN                  (0)                     //电机PWM占空比最小值，过小可能电机无法驱动[需要修改]

void motor_all_init();
void motor_all_pwm_set_duty(uint32 duty);
void motor_left_pwm_set_duty(uint32 duty);
void motor_right_pwm_set_duty(uint32 duty);
void motor_all_close(void);

#endif /* CODE_MOTOR_H_ */
