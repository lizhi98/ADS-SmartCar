/*
 * cameraTest.c
 *
 *  Created on: 2024年11月21日
 *      Author: Koishi
 */

#include "./cameraTest.h"

uint8  mt9v03x_image_dis[MT9V03X_W * 2][MT9V03X_H * 2];

void camera_test(void) {
#if(1)
    printf("mt9v03x_set_exposure_time\n");
    //mt9v03x_set_exposure_time(100);

    printf("mt9v03x_init\n");
    mt9v03x_init();

    while (1) {
        if (mt9v03x_finish_flag) {


            ips200_show_gray_image(0, 0, mt9v03x_image[0], MT9V03X_W, MT9V03X_H, ips200_width_max, ips200_height_max, 0);

            mt9v03x_finish_flag = 0;
            //system_delay_ms(3000);
        }
    }
#endif

#if(0)

    while(1){

        printf("%d",-1);

        for(int i=0;i<MT9V03X_H;i++){
            for(int k = 0;k<MT9V03X_W;k++){

    //            imgData[i][k]=(short)i;
                printf("%c",i);
                system_delay_ms(1000);

            }
        }
        printf("%d",-2);


        system_delay_ms(1000);
    }


#endif

}

