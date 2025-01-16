#include "pid.h"

PIDConfig    motor_pid_config;
PIDConfig    steer_pid_config;

PIDCalc      motor_left_pid_calc;
PIDCalc      motor_right_pid_calc;
PIDCalc      steer_pid_calc;

void pid_init(void){
    motor_pid_config.KP = PID_MOTOR_INIT_KP;
    motor_pid_config.KI = PID_MOTOR_INIT_KI;
    motor_pid_config.KD = PID_MOTOR_INIT_KD;
    
    steer_pid_config.KP = PID_STEER_INIT_KP;
    steer_pid_config.KI = PID_STEER_INIT_KI;
    steer_pid_config.KD = PID_STEER_INIT_KD;
}
