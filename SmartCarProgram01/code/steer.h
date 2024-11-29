/*
 * steer.h
 *
 *  Created on: 2024年11月28日
 *      Author: lizhi
 */

#ifndef CODE_STEER_H_
#define CODE_STEER_H_

#include<zf_driver_pwm.h>

#define steerPwmPin ATOM0_CH1_P33_9
#define steerPwmInitFreq 50 //单位HZ
#define steerPwmInitDuty 750 //0-10000



void steer_init(void);
void steer_set_freq(uint32 freq);
void steer_set_duty(uint32 duty);
void steer_plus_duty(int16 plusDuty);  //减少duty请使用负数

#endif /* CODE_STEER_H_ */
