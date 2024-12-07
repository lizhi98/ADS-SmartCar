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
#include"steer.h"
#include"stdlib.h"
#include"image.h"

#define MOTOR_PWM_PLUS_PER_RUN          25
//#define MOTOR_MAKE_STOP_PWM_DUTY        (PWM_DUTY_MAX*0.5)

extern int16 	motorLeftSetSpeed;
extern int16 	motorRightSetSpeed;
extern int16    motorLeftSpeed;
extern int16    motorRightSpeed;

extern uint32 	motorLeftForwardPwmPresentDuty;
extern uint32 	motorLeftBackwardPwmPresentDuty;
extern uint32 	motorRightForwardPwmPresentDuty;
extern uint32 	motorRightBackwardPwmPresentDuty;

//-25°——25°为有效值 小于-25°都是-25°，大于25°都是25°
extern int8 	steerSetAngle;

struct MotorPIDConfig{
        int KP;
        int KI;
        int KD;
        int current;
        int target;
        int error;
        int lastError;
        int last2Error;
        int out;
};

struct SteerPIDConfig{
        int KP;
        int KI;
        int KD;
        int current;
        double target;
        int error;
        int lastError;
        int last2Error;
        int out;
};

//==============V1==============
//让电机速度调整到设定值
void motor_make_same_with_seting(void);
//让舵机角度调整到设定值
void steer_make_same_with_setting(void);

//==============V2==============(没写完，不要用)
void motor_pid_calc(struct MotorPIDConfig * pid);
void motor_pid_call();
void steer_pid_call();

#endif /* CODE_PID_H_ */
