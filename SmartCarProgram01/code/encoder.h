/*
 * encoder.h
 *
 *  Created on: 2024年11月28日
 *      Author: lizhi
 */

#ifndef CODE_ENCODER_H_
#define CODE_ENCODER_H_

#include<zf_driver_encoder.h>

#define encoderLeftCountPin TIM5_ENCODER_CH1_P10_3
#define encoderLeftDirPin TIM5_ENCODER_CH2_P10_1
#define encoderLeftTIM TIM5_ENCODER
#define encoderRightCountPin TIM6_ENCODER_CH1_P20_3
#define encoderRightDirPin TIM6_ENCODER_CH2_P20_0
#define encoderRightTIM TIM6_ENCODER

void encoder_init(void);
float32 encoder_get_speed(uint8 encoderTIM);
void encoder_all_clear(void);

#endif /* CODE_ENCODER_H_ */
