/*
 * steer.h
 *
 *  Created on: 2024年11月28日
 *      Author: lizhi
 */

#ifndef CODE_STEER_H_
#define CODE_STEER_H_

#include<zf_driver_pwm.h>

#define STEER_PWM_PIN 				ATOM0_CH1_P33_9
#define STEER_PWM_FREQ_STD 		    50  //官方推荐的频率50，单位HZ
#define STEER_PWM_DUTY_MID 			782 //舵机位于中间时的PWM占空比，需要根据小车实际修改780
#define STEER_PWM_DUTY_CURVE_DELTA  80  //舵机在转弯时的PWM占空比偏移量，需要根据小车实际修改
#define STEER_PWM_DUTY_LEFT_LIM 	832 //舵机位于左转极限时的PWM占空比，需要根据小车实际修改
#define STEER_PWM_DUTY_RIGHT_LIM 	732 //舵机位于右转极限时的PWM占空比，需要根据小车实际修改

extern uint32 steerPresentDuty;

void steer_init(void);
void steer_set_freq(uint32 freq);
void steer_set_duty(uint32 duty);
void steer_plus_duty(int plusDuty);  //减少duty请使用负数
void steer_print_duty(void);

#endif /* CODE_STEER_H_ */
