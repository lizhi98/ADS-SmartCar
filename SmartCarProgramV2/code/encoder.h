/*
 * encoder.h
 *
 *  Created on: 2024年11月28日
 *      Author: lizhi
 */

#ifndef CODE_ENCODER_H_
#define CODE_ENCODER_H_

#include<zf_driver_encoder.h>
#include<zf_driver_pit.h>
#include "pid.h"

#define ENCODER_LEFT_COUNT_PIN      TIM2_ENCODER_CH1_P33_7
#define ENCODER_LEFT_DIR_PIN        TIM2_ENCODER_CH2_P33_6
#define ENCODER_LEFT_TIM            TIM2_ENCODER

#define ENCODER_RIGHT_COUNT_PIN     TIM4_ENCODER_CH1_P02_8
#define ENCODER_RIGHT_DIR_PIN       TIM4_ENCODER_CH2_P00_9
#define ENCODER_RIGHT_TIM           TIM4_ENCODER

#define ENCODER_PIT_CH              CCU60_CH0
#define ENCODER_GET_COUNT_INTERVAL  50


#define get_left_motor_speed()     ( encoder_get_count(ENCODER_LEFT_TIM)  * 10     /   ENCODER_GET_COUNT_INTERVAL )
#define get_right_motor_speed()    ( encoder_get_count(ENCODER_RIGHT_TIM) * 10     /   ENCODER_GET_COUNT_INTERVAL )

void encoder_get_speed(void);
void encoder_all_clear(void);
void encoder_init(void);

#endif
