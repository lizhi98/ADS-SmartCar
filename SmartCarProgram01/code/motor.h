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
#define motor1PwmPin1 ATOM1_CH4_P02_4
#define motor1PwmPin2 ATOM1_CH5_P02_5
#define motor2PwmPin1 ATOM1_CH6_P02_6
#define motor2PwmPin2 ATOM1_CH7_P02_7

#endif /* CODE_MOTOR_H_ */
