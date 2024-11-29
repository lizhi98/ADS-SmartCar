/*
 * steer.c
 *
 *  Created on: 2024年11月28日
 *      Author: lizhi
 */
#include"steer.h"
static uint16 steerCurrentDuty = steerPwmInitDuty;

void steer_init(void){
    pwm_init(steerPwmPin, steerPwmInitFreq, steerPwmInitDuty);
    printf("steerInit OK!");
}

//强烈不建议使用，逐飞没有提供更改频率的接口，需要重新初始化
void steer_set_freq(uint32 freq){
    pwm_init(steerPwmPin, freq, steerCurrentDuty);
}

void steer_set_duty(uint32 duty){
    if(duty > PWM_DUTY_MAX){
        return;
    }
    pwm_set_duty(steerPwmPin,duty);
}

/*
 * 函数作用：让占空比变为 当前占空比频率+plusDuty
 * 参数说明：如果需要减少duty请让plusDuty为负数
 *          最大占空比为PWM_DUTY_MAX （10000）
 * 注意事项：若预期占空比超过10000，将会赋最大占空比
 *          若预期占空比小于0，将会赋0
 */
void steer_plus_duty(int16 plusDuty){
    int16 dutyTemp = steerCurrentDuty + plusDuty;
    if(dutyTemp > PWM_DUTY_MAX){
        pwm_set_duty(steerPwmPin,PWM_DUTY_MAX);
    }else if(dutyTemp < 0){
        pwm_set_duty(steerPwmPin,0);
    }else{
        pwm_set_duty(steerPwmPin,dutyTemp);
        steerCurrentDuty = dutyTemp;
        printf("set OK");
    }

}

