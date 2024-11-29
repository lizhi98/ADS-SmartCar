/*
 * encoder.c
 *
 *  Created on: 2024年11月28日
 *      Author: lizhi
 */
#include"encoder.h"

void encoder_init(void){
    encoder_dir_init(encoderLeftTIM,encoderLeftCountPin,encoderLeftDirPin);
    encoder_dir_init(encoderRightTIM,encoderRightCountPin,encoderRightDirPin);
}


void encoder_all_clear(void){
    encoder_clear_count(encoderLeftTIM);
    encoder_clear_count(encoderRightTIM);
}
