/*
 * steer.h
 *
 *  Created on: 2024年11月28日
 *      Author: lizhi
 */

#ifndef CODE_STEER_H_
#define CODE_STEER_H_

#include<zf_driver_pwm.h>
#include"screen.h"

#define STEER_PWM_PIN 				ATOM2_CH2_P33_6
#define STEER_PWM_FREQ_STD 		    50 //官方推荐的频率50，单位HZ
#define STEER_PWM_DUTY_MID 			780 //舵机位于中间时的PWM占空比，需要根据小车实际修改780
#define STEER_PWM_DUTY_LEFT_LIM 	828 //舵机位于左转极限时的PWM占空比，需要根据小车实际修改
#define STEER_PWM_DUTY_RIGHT_LIM 	732 //舵机位于右转极限时的PWM占空比，需要根据小车实际修改

void steer_init(void);
void steer_set_freq(uint32 freq);
void steer_set_duty(uint32 duty);
void steer_plus_duty(int16 plusDuty);  //减少duty请使用负数
void steer_print_duty(void);

#endif /* CODE_STEER_H_ */
