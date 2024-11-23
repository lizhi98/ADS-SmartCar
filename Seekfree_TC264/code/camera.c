/*
 * camera.c
 *
 *  Created on: 2024年11月23日
 *      Author: lizhi
 */
#include"camera.h"
#if(0)
void camera_init(void){

    mt9v03x_set_exposure_time(EXPOSURE_TIME);

    printf("mt9v03x_initing...");
    if(mt9v03x_init()){
        printf("mt9v03x_init failed!!!");
    }
    printf("mt9v03x_init success!!!");

    while (1) {
        if (mt9v03x_finish_flag) {
            
            printf("CAMERA_START\n");
            for (int i = 0; i < MT9V03X_H; i ++) {
                for (int j = 0; j < MT9V03X_W; j ++) {
                    printf("%c", mt9v03x_image[i][j]);
                }
            }

            printf("CAMERA_END\n");

            mt9v03x_finish_flag = 0;
            
            system_delay_ms(3000);
        }
    }



}
#endif
