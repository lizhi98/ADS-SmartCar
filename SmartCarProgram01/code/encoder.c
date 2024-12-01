/*
 * encoder.c
 *
 *  Created on: 2024年11月28日
 *      Author: lizhi
 */
#include"encoder.h"

void encoder_init(void){
    encoder_dir_init(ENCODER_LEFT_TIM,ENCODER_LEFT_COUNT_PIN,ENCODER_LEFT_DIR_PIN);
    encoder_dir_init(ENCODER_RIGHT_TIM,ENCODER_RIGHT_COUNT_PIN,ENCODER_RIGHT_DIR_PIN);
}


void encoder_all_clear(void){
    encoder_clear_count(ENCODER_LEFT_TIM);
    encoder_clear_count(ENCODER_RIGHT_TIM);
}
