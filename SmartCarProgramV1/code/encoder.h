/*
 * encoder.h
 *
 *  Created on: 2024年11月28日
 *      Author: lizhi
 */

#ifndef CODE_ENCODER_H_
#define CODE_ENCODER_H_

#include<zf_driver_encoder.h>

#define ENCODER_LEFT_COUNT_PIN TIM5_ENCODER_CH1_P10_3
#define ENCODER_LEFT_DIR_PIN TIM5_ENCODER_CH2_P10_1
#define ENCODER_LEFT_TIM TIM5_ENCODER
#define ENCODER_RIGHT_COUNT_PIN TIM6_ENCODER_CH1_P20_3
#define ENCODER_RIGHT_DIR_PIN TIM6_ENCODER_CH2_P20_0
#define ENCODER_RIGHT_TIM TIM6_ENCODER

#define get_left_motor_speed()      encoder_get_count(ENCODER_LEFT_TIM)
#define get_right_motor_speed()     encoder_get_count(ENCODER_RIGHT_TIM)

void encoder_init(void);
void encoder_all_clear(void);

#endif /* CODE_ENCODER_H_ */
