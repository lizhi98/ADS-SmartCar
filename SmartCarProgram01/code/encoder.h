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

void encoder_init(void);
float32 encoder_get_speed(uint8 encoderTIM);
void encoder_all_clear(void);

#endif /* CODE_ENCODER_H_ */
