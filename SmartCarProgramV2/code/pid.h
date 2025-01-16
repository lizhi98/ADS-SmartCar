#ifndef CODE_PID_H_
#define CODE_PID_H_

#include "zf_common_typedef.h"

#define PID_MOTOR_INIT_KP 0
#define PID_MOTOR_INIT_KI 0
#define PID_MOTOR_INIT_KD 0

#define PID_STEER_INIT_KP 0
#define PID_STEER_INIT_KI 0
#define PID_STEER_INIT_KD 0

typedef struct _pid_config
{
    float KP;
    float KI;
    float KD;
} PIDConfig;

typedef struct _pid_calc
{
    int current;
    int target;
    int error;
    int lastError;
    int last2Error;
    int out;
} PIDCalc;

extern PIDConfig    motor_pid_config;
extern PIDConfig    steer_pid_config;

extern PIDCalc      motor_left_pid_calc;
extern PIDCalc      motor_right_pid_calc;
extern PIDCalc      steer_pid_calc;

void pid_calc(PIDConfig * pid_config,PIDCalc * pid_calc);
void pid_init(void);

#endif // CODE_PID_H_
