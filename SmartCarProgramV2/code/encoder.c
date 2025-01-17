/*
 * encoder.c
 *
 *  Created on: 2024年11月28日
 *      Author: lizhi
 */
#include"encoder.h"

void encoder_init(void){
    encoder_quad_init(ENCODER_RIGHT_TIM,    ENCODER_RIGHT_COUNT_PIN,    ENCODER_RIGHT_DIR_PIN);
    encoder_quad_init(ENCODER_LEFT_TIM,     ENCODER_LEFT_COUNT_PIN,     ENCODER_LEFT_DIR_PIN);
    pit_ms_init (     ENCODER_PIT_CH,       ENCODER_GET_COUNT_INTERVAL);
}
void encoder_all_clear(void){
    encoder_clear_count(ENCODER_LEFT_TIM);
    encoder_clear_count(ENCODER_RIGHT_TIM);
}
void encoder_get_speed(void){
    motor_left_pid_calc.current   =  get_left_motor_speed();
    motor_right_pid_calc.current  =  (-1) * get_right_motor_speed();
}
