/*
 * steer.c
 *
 *  Created on: 2024年11月28日
 *      Author: lizhi
 */
#include"steer.h"

uint32   steerPresentDuty;
int8     steerSetAngle;

void steer_init(void){
    pwm_init(STEER_PWM_PIN, STEER_PWM_FREQ_STD, STEER_PWM_DUTY_MID);
    steerPresentDuty = STEER_PWM_DUTY_MID;
    steer_print_duty();
}

//强烈不建议使用，逐飞没有提供更改频率的接口，需要重新初始化
void steer_set_freq(uint32 freq){
    pwm_init(STEER_PWM_PIN, freq, steerPresentDuty);
}

/*
 * 函数作用：让占空比变为duty
 * 注意事项：
 *          1. 若预期占空比超过了左极限，则会赋值左极限
 *          2. 若预期占空比小于右极限，则会赋值右极限
 */
void steer_set_duty(uint32 duty){
    if (duty > STEER_PWM_DUTY_LEFT_LIM) {
        pwm_set_duty(STEER_PWM_PIN,STEER_PWM_DUTY_LEFT_LIM);
        steerPresentDuty = STEER_PWM_DUTY_LEFT_LIM;
    }
    else if (duty < STEER_PWM_DUTY_RIGHT_LIM){
        pwm_set_duty(STEER_PWM_PIN,STEER_PWM_DUTY_RIGHT_LIM);
        steerPresentDuty = STEER_PWM_DUTY_RIGHT_LIM;
    }
    else {
        pwm_set_duty(STEER_PWM_PIN,duty);
        steerPresentDuty = duty;
    }
    steer_print_duty();
}

/*
 * 函数作用：让占空比变为 当前占空比频率+plusDuty
 * 参数说明：如果需要减少duty请让plusDuty为负数
 *          调用steer_set_duty函数来实现占空比设置
 * 注意事项：
 *          1. 若预期占空比超过了左极限，则会赋值左极限
 *          2. 若预期占空比小于右极限，则会赋值右极限
 */
void steer_plus_duty(int16 plusDuty){
    steer_set_duty(steerPresentDuty + plusDuty);
}

void steer_print_duty(void){
#if(0)
    char arg[16];
    sprintf(arg,"steerDuty:%ld",steerPresentDuty);
    screen_show_string(arg);
#endif
}
