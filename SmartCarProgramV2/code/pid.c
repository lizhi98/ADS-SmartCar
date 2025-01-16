#include "pid.h"

pid motor_left_pid;
pid motor_right_pid;
pid steer_pid;


void pid_set_kp(int kp, pid* pid){
    pid->KP = kp;
}
void pid_set_ki(int ki, pid* pid){
    pid->KI = ki;
}
void pid_set_kd(int kd, pid* pid){
    pid->KD = kd;
}

void pid_p_plus(int16 delta, pid* pid){
    pid->KP += delta;
}
void pid_i_plus(int16 delta, pid* pid){
    pid->KI += delta;
}
void pid_d_plus(int16 delta, pid* pid){
    pid->KD += delta;
}

void pid_init(void){
    motor_left_pid.KP = PID_MOTOR_INIT_KP;
    motor_left_pid.KI = PID_MOTOR_INIT_KI;
    motor_left_pid.KD = PID_MOTOR_INIT_KD;
    steer_pid.KP = PID_STEER_INIT_KP;
    steer_pid.KI = PID_STEER_INIT_KI;
    steer_pid.KD = PID_STEER_INIT_KD;
     
}
