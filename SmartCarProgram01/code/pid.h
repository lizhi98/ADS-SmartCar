/*
 * pid.h
 *
 *  Created on: 2024年12月3日
 *      Author: lizhi
 */

#ifndef CODE_PID_H_
#define CODE_PID_H_

#include"motor.h"
#include"encoder.h"
#include"stdlib.h"

#define MOTOR_PWM_PLUS_PER_RUN          20
#define MOTOR_MAKE_STOP_PWM_DUTY        (PWM_DUTY_MAX*0.5)

extern int16 motorLeftSetSpeed;
extern int16 motorRightSetSpeed;
extern uint32 motorLeftForwardPwmPresentDuty;
extern uint32 motorLeftBackwardPwmPresentDuty;
extern uint32 motorRightForwardPwmPresentDuty;
extern uint32 motorRightBackwardPwmPresentDuty;
extern int16 motorLeftSpeed;
extern int16 motorRightSpeed;

//让电机速度调整到设定值(增量式)
void motor_make_same_with_seting(void);
//让舵机角度调整到设定值(位置式)
void steer_make_same_with_setting(void);

#endif /* CODE_PID_H_ */
