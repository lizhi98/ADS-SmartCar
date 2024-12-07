/*
 * uartWireless.c
 *
 *  Created on: 2024年12月3日
 *      Author: lizhi
 */
#include"uartWireless.h"

void uart_wireless_send_image(){
    mt9v03x_init();
    if(wireless_uart_init()){
        printf("uart_wireless Unit failed!");
    }
    while(1){

        if(mt9v03x_finish_flag){
            wireless_uart_send_image(&mt9v03x_image[0][0], MT9V03X_IMAGE_SIZE);
            system_delay_ms(1000);
            mt9v03x_finish_flag=0;
        }

    }


}
