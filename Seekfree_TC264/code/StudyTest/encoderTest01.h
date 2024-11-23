/*
 * Test01.h
 *
 *  Created on: 2024年11月19日
 *      Author: koishi
 */

#ifndef CODE_TEST01_H_
#define CODE_TEST01_H_

#include <zf_driver_encoder.h>
#include <zf_driver_delay.h>
#include <zf_driver_pit.h>

//编码器1引脚定义
#define ENCODER1_TIM TIM2_ENCODER
#define ENCODER1_Ch1_Pin TIM2_ENCODER_CH1_P33_7 //计数引脚
#define ENCODER1_Ch2_Pin TIM2_ENCODER_CH2_P33_6 //计数方向引脚
//编码器2引脚定义
#define ENCODER2_TIM TIM4_ENCODER
#define ENCODER2_Ch1_Pin TIM4_ENCODER_CH1_P02_8 //计数引脚
#define ENCODER2_Ch2_Pin TIM4_ENCODER_CH2_P00_9 //计数方向引脚

void encoder_test_01(void);

void encoder1_print(void);
void encoder2_print(void);



#endif /* CODE_TEST01_H_ */

