#include "screen.h"

ObjectData objectData;

void screen_init() {
    ips200_init(SCREEN_LINK_TYPE);
    ips200_full(RGB565_BLACK);
}
void screen_clear(void){
    ips200_clear();
    ips200_full(RGB565_BLACK);
}
void screen_show_image(ImageBase image) {
    ips200_displayimage03x(image,MT9V03X_W,MT9V03X_H);
}
//留出图像位置
void screen_show_text(text text) {
    ips200_show_string(0,MT9V03X_H + 5,text);
}


void screen_show_menu(void){
    
}
void screen_show_objects(){
    //显示图像
    if (SWITCH_IMAGE)
    {
        screen_show_image(mt9v03x_image[0]);
    }
    // angle:82.256 time:1000 eleType:1 leftS:3000 righS:4000 
    char text[60],temp[15];
    if(SWITCH_ANGLE)                { sprintf(temp,"angle:%5f\n",objectData.angle);         strcat(text,temp); }
    if(SWITCH_IMAGE_PROCESS_TIME)   { sprintf(temp,"time:%d\n",objectData.imageProcessTime);strcat(text,temp); }
    if(SWITCH_ELEMENT_TYPE)         { sprintf(temp,"eleType:%u\n",objectData.elementType);  strcat(text,temp); }
    if(SWITCH_MOTOR_LEFT_SPEED)     { sprintf(temp,"leftS:%d\n",objectData.leftMotorS);     strcat(text,temp); }
    if(SWICTH_MOTOR_RIGHT_SPEED)    { sprintf(temp,"righS:%d\n",objectData.rightMotorS);    strcat(text,temp); }
    screen_show_text(text);
}
void screen_wrong(void){
    screen_clear();
    // ips200_full(RGB565_BLACK);
    ips200_show_string(0,0,"Wrong!!!\nPlease Restart!!");
}


