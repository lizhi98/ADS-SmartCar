/*
 *
 */

#include <StudyTest/encoderTest01.h>



int16 encoder1Count;
int16 encoder2Count;

void encoder_test_01(){


    //3V3方向编码器初始化
    encoder_dir_init(ENCODER1_TIM, ENCODER1_Ch1_Pin, ENCODER1_Ch2_Pin); //编码器1初始化
    encoder_dir_init(ENCODER2_TIM, ENCODER2_Ch1_Pin, ENCODER2_Ch2_Pin); //编码器2初始化

    while(1){
        system_delay_ms(1000);
        encoder1_print();
        encoder2_print();

//        pit_ms_init(CCU60_CH0, 500);
//        pit_enable(CCU60_CH0);
//        pit_start(CCU60_CH0);
    }

}




/*
 * function：简单地把编码器1的1s内的差值打印到串口控制台
 */
void encoder1_print(){
    int encoder1CountOld = encoder1Count;
    encoder1Count = encoder_get_count(ENCODER1_TIM);
    int16 delta = encoder1Count - encoder1CountOld;

    printf("encoder1: %d (%+d)\n", encoder1Count, delta);
}

/*
 * function：简单地把编码器2的1s内的差值打印到串口控制台
 */
void encoder2_print(){
    int encoder2CountOld = encoder2Count;
    encoder2Count = encoder_get_count(ENCODER2_TIM);
    int16 delta = encoder2Count - encoder2CountOld;

    printf("encoder2: %d (%+d)\n", encoder2Count, delta);
}
