/*
 * screen.c
 *
 *  Created on: 2024年11月29日
 *      Author: lizhi
 */
#include"screen.h"

void screen_init(void){
    ips200_init(IPS200_TYPE_SPI);
}

void screen_show_string(char str[]){
    ips200_show_string(0, 0, str);
}
