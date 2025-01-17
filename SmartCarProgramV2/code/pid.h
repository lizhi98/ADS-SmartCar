#ifndef CODE_PID_H_
#define CODE_PID_H_

#include "zf_common_typedef.h"

#define PID_MOTOR_INIT_KP 0.2f
#define PID_MOTOR_INIT_KI 0.01f
// #define PID_MOTOR_INIT_KD 0.0f

#define PID_STEER_INIT_KP -2.0f
// #define PID_STEER_INIT_KI 1.0f
#define PID_STEER_INIT_KD 0.3f

#define PID_CALC_INTERVAL_MOTOR 5
#define PID_CALC_INTERVAL_STEER 3

#define PID_MOTOR_MAX_INTEGRAL 100
#define PID_STEER_MAX_INTEGRAL 20

#define PID_PIT_CH_MOTOR CCU60_CH1
#define PID_PIT_CH_STEER CCU61_CH0

typedef struct _pid_config {
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
    float integral;
    float out;
} PIDCalc;

extern PIDConfig    motor_pid_config;
extern PIDConfig    steer_pid_config;

extern PIDCalc      motor_left_pid_calc;
extern PIDCalc      motor_right_pid_calc;
extern PIDCalc      steer_pid_calc;

// motor
//int motor_calc(PIDConfig* pid_config, PIDCalc* pi_calc);
// steer
//int steer_calc(PIDConfig* pid_config, PIDCalc* pd_calc);

void pid_set_motor_target(int speed);
void pid_set_steer_target(int duty);

int motor_calc(PIDConfig *pid_config , PIDCalc *pid_calc);
float steer_calc(PIDConfig *pid_config , PIDCalc *pd_calc);

void pid_start_calc(void);
void pid_stop_calc_and_clear(void);
void pid_init(void);

#endif
