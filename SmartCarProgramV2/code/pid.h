#ifndef CODE_PID_H_
#define CODE_PID_H_

#include "zf_common_typedef.h"

#define PID_MOTOR_INIT_KP 0
#define PID_MOTOR_INIT_KI 0
#define PID_MOTOR_INIT_KD 0

#define PID_STEER_INIT_KP 0
#define PID_STEER_INIT_KI 0
#define PID_STEER_INIT_KD 0

#define pid_set_motor_left_kp(kp)   pid_set_kp(kp, &motor_left_pid)
#define pid_set_motor_left_ki(ki)   pid_set_ki(ki, &motor_left_pid)
#define pid_set_motor_left_kd(kd)   pid_set_kd(kd, &motor_left_pid)
#define pid_set_motor_right_kp(kp)  pid_set_kp(kp, &motor_right_pid)
#define pid_set_motor_right_ki(ki)  pid_set_ki(ki, &motor_right_pid)
#define pid_set_motor_right_kd(kd)  pid_set_kd(kd, &motor_right_pid)

#define pid_set_steer_kp(kp)    pid_set_kp(kp, &steer_pid)
#define pid_set_steer_ki(ki)    pid_set_ki(ki, &steer_pid)
#define pid_set_steer_kd(kd)    pid_set_kd(kd, &steer_pid)

typedef struct _pid
{
    int KP;
    int KI;
    int KD;
    int current;
    double target;
    int error;
    int lastError;
    int last2Error;
    int out;
} pid;

void pid_set_kp(int kp, pid* pid);
void pid_set_ki(int ki, pid* pid);
void pid_set_kd(int kd, pid* pid);

void pid_p_plus(int16 delta, pid* pid);
void pid_i_plus(int16 delta, pid* pid);
void pid_d_plus(int16 delta, pid* pid);

void pid_init(void);

#endif // CODE_PID_H_