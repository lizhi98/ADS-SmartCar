/*
 * assert.c
 *
 *  Created on: 2025年1月11日
 *      Author: lizhi
 */
#include "code/assert.h"
void wrong(void){
    screen_clear();
    screen_show_string(0, 0, "WRONG!!!");
    while(1);
}

