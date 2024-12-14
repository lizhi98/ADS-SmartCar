#ifndef CODE_MENU_H_
#define CODE_MENU_H_

#include"screen.h"
#include"key.h"

#define LINE_GAP 30

//定义选项位置 0行固定为"MENU" 
typedef enum{
    //===================BACK AND "MENU"==========
    MENU_LINE,            BACK_LINE,
    //===================Main MENU================
    GO_LINE=1,            GO_AND_SHOW_CONFIG_LINE,    SPEED_LINE,         PID_LINE,               
    //===================SPEED MENU===============
    MOTOR_SPEED_K_LINE=2, NORMOL_SPEED_LINE,          CURVE_SPEED_LINE,        
    //===================PID MENU=================
    KP_LINE=2,            KI_LINE,                    KD_LINE,                 
}Location;

typedef enum {
    init,
    GO,             GO_AND_SHOW_CONFIG,     SPEED,          PID,    //主菜单
    BACK,                                                       //返回到主菜单
    MOTOR_SPEED_K,  NORMOL_SPEED_RAW,       CURVE_SPEED_RAW,        //速度调节菜单
    KP,             KI,                     KD,                 //PID调节菜单
}OptionIndex;

typedef enum{
    PAGE_MAIN,
    PAGE_SPEED_CONFIG,
    PAGE_PID_CONFIG,
}Pages;

void show_main_menu(void);
void show_speed_menu(void);
void show_pid_menu(void);

void menu_update(void);
void menu_jump(Pages target);
void edit_config(KeyIndex key);

void key_control(KeyIndex key);

#endif
