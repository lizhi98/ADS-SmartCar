/*
 * camera.c
 *
 *  Created on: 2024年11月23日
 *      Author: lizhi
 */

#include"camera.h"

struct Control {

};

Control getControl(*uint8[MT9V03X_W] image) {
    while (1) {
        if (mt9v03x_finish_flag) {


            ips200_show_gray_image(0, 0, mt9v03x_image[0], MT9V03X_W, MT9V03X_H, MT9V03X_W, MT9V03X_H, 0);

            mt9v03x_finish_flag = 0;
            //system_delay_ms(3000);
        }
    }
}
