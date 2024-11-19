/*
 *
 */

#include <Test/encoderTest01.h>
#include<zf_driver_delay.h>


int16 encoder1Count;
int16 encoder1Count_Temp;
int16 encoder2Count;
int16 encoder2Count_Temp;

void encoderTest01(){


    //3V3方向编码器初始化
    encoder_dir_init(ENCODER1_TIM, ENCODER1_Ch1_Pin, ENCODER1_Ch2_Pin); //编码器1初始化
    encoder_dir_init(ENCODER2_TIM, ENCODER2_Ch1_Pin, ENCODER2_Ch2_Pin); //编码器2初始化

    while(1){

        encoder1Print();

        encoder2Print();


    }

}

/*
 * function：简单地把编码器1的1s内的差值打印到串口控制台
 */
void encoder1Print(){

    encoder1Count_Temp = encoder_get_count(ENCODER1_TIM);
    system_delay_ms(1000);
    encoder1Count = encoder_get_count(ENCODER1_TIM);
    int16 Cha = encoder1Count_Temp - encoder1Count;

    printf("encoder1:%d",Cha);

}

/*
 * function：简单地把编码器2的1s内的差值打印到串口控制台
 */
void encoder2Print(){

    encoder2Count_Temp = encoder_get_count(ENCODER2_TIM);
    system_delay_ms(1000);
    encoder2Count = encoder_get_count(ENCODER2_TIM);
    int16 Cha = encoder2Count_Temp - encoder2Count;

    printf("encoder2:%d",Cha);

}
