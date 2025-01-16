#include "menu.h"
#include "string.h"

MenuItem menu_items[MENU_ITEM_COUNT] = {
    // index          next,                   back
    // MAIN
    {START,           menu_start,             NULL,   START, SETTINGS},
    {START_WITH_INFO, menu_start_with_info,   NULL,   START, SETTINGS},
    {SETTINGS,        menu_show_settings,     NULL,   START, SETTINGS},
    // SETTINGS
    {PID,             menu_show_pid,          menu_show_main, PID, IMAGE},
    {SPEED,           menu_show_speed,        menu_show_main, PID, IMAGE},
    {IMAGE,           menu_show_image,        menu_show_main, PID, IMAGE},
    // PID
    {KP,              menu_set_pid_p,         menu_show_settings,   KP, KD},
    {KI,              menu_set_pid_i,         menu_show_settings,   KP, KD},
    {KD,              menu_set_pid_d,         menu_show_settings,   KP, KD},
    // SPEED
    {NORMAL_SPEED,    menu_set_speed_normal,  menu_show_settings,   NORMAL_SPEED, CURVE_SPEED},
    {CURVE_SPEED,     menu_set_speed_curve,   menu_show_settings,   NORMAL_SPEED, CURVE_SPEED},
    // IMAGE
    {IMAGE1,          menu_set_image1,        menu_show_settings,   IMAGE1, IMAGE5},
    {IMAGE2,          menu_set_image2,        menu_show_settings,   IMAGE1, IMAGE5},
    {IMAGE3,          menu_set_image3,        menu_show_settings,   IMAGE1, IMAGE5},
    {IMAGE4,          menu_set_image4,        menu_show_settings,   IMAGE1, IMAGE5},
    {IMAGE5,          menu_set_image5,        menu_show_settings,   IMAGE1, IMAGE5},
};
const char * menu_names[MENU_ITEM_COUNT] = {
    // MAIN
    "START",        "START_WITH_INFO",      "SETTINGS",
    // SETTINGS
    "PID",          "SPEED",                "IMAGE",
    // PID
    "KP",           "KI",                   "KD",
    // SPEED
    "NORMAL_SPEED", "CURVE_SPEED",
    // IMAGE
    "IMAGE1",       "IMAGE2",               "IMAGE3",   "IMAGE4",   "IMAGE5",
};

MenuIndex   menu_current_index;

void menu_init(void){
    
    // 清屏
    screen_clear();
    // 显示默认菜单
    menu_show_main();
    // while(TRUE){

    // }
}

// 菜单项目显示函数
void menu_show(MenuIndex startIndex,MenuIndex endIndex){
    screen_clear();
    menu_show_pointer();
    screen_show_string(30, 0, "Menu");
    for(int i = startIndex; i <= endIndex; i++){
        screen_show_string(10, (i - startIndex + 1) * LINE_GAP, menu_names[i]);
    }
}
void menu_show_pointer(void){
    screen_show_string(0, (menu_current_index - menu_items[menu_current_index].thisPageStart + 1) * LINE_GAP, ">");
}
// 菜单显示函数
void menu_show_main(void){
    menu_current_index = START;
    menu_show(START, SETTINGS);
}
void menu_show_settings(void){
    menu_current_index = PID;
    menu_show(PID, IMAGE);
}
void menu_show_pid(void){
    menu_current_index = KP;
    menu_show(KP, KD);
}
void menu_show_speed(void){
    menu_current_index = NORMAL_SPEED;
    menu_show(NORMAL_SPEED, CURVE_SPEED);
}
void menu_show_image(void){
    menu_current_index = IMAGE1;
    menu_show(IMAGE1, IMAGE5);
}

// 车启动类函数
void menu_start(void){
    screen_clear();
    screen_show_string(0, 0, "PRESS ANY KEY TO STOP");
}
void menu_start_with_info(void){
    screen_clear();
    screen_show_string(0, 0, "PLEASE WAIT...");
}

// 设置项目函数
void menu_set_pid_p(void){
    screen_clear();
    screen_show_string(0, 0, "KP");
}
void menu_set_pid_i(void){
    screen_clear();
    screen_show_string(0, 0, "KI");
}
void menu_set_pid_d(void){
    screen_clear();
    screen_show_string(0, 0, "KD");
}

void menu_set_speed_normal(void){
    screen_clear();
    screen_show_string(0, 0, "NORMAL_SPEED");
}
void menu_set_speed_curve(void){
    screen_clear();
    screen_show_string(0, 0, "CURVE_SPEED");
}

void menu_set_image1(void){
    screen_clear();
    screen_show_string(0, 0, "IMAGE1");
}
void menu_set_image2(void){
    screen_clear();
    screen_show_string(0, 0, "IMAGE2");
}
void menu_set_image3(void){
    screen_clear();
    screen_show_string(0, 0, "IMAGE3");
}
void menu_set_image4(void){
    screen_clear();
    screen_show_string(0, 0, "IMAGE4");
}
void menu_set_image5(void){
    screen_clear();
    screen_show_string(0, 0, "IMAGE5");
}

// 调用执行函数
void menu_select_next(void){
    if(menu_current_index + 1 > menu_items[menu_current_index].thisPageEnd){
        menu_current_index = menu_items[menu_current_index].thisPageStart;
    }else{
        menu_current_index++;
    }
    menu_show(menu_items[menu_current_index].thisPageStart, menu_items[menu_current_index].thisPageEnd);
}
void menu_select_last(void){
    if(menu_current_index - 1 < menu_items[menu_current_index].thisPageStart){
        menu_current_index = menu_items[menu_current_index].thisPageEnd;
    }else{
        menu_current_index--;
    }
    menu_show(menu_items[menu_current_index].thisPageStart, menu_items[menu_current_index].thisPageEnd);
}
void menu_ok(void){
    if (menu_items[menu_current_index].next!=NULL)
    {   
        menu_items[menu_current_index].next();
    }
}
void menu_back(void){
    if (menu_items[menu_current_index].back!=NULL)
    {
        menu_items[menu_current_index].back();
    }
}
