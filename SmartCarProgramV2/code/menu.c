#include "menu.h"
#include "pid.h"
#include "motor.h"
#include "steer.h"
#include "string.h"
#include "zf_driver_delay.h"
extern uint32 time_per_image;
MenuItem menu_items[MENU_ITEM_COUNT] = {
    // name             index            next,                   back   thisPageStart   thisPageEnd
    // MAIN
    {"START",           START,           menu_start,             NULL,              START,         SETTINGS},
    {"START_WITH_INFO", START_WITH_INFO, menu_start_with_info,   NULL,              START,         SETTINGS},
    {"SETTINGS",        SETTINGS,        menu_show_settings,     NULL,              START,         SETTINGS},
    // SETTINGS
    {"PID",             PID,             menu_show_pid,          menu_show_main,    PID, IMAGE},
    {"SPEED",           SPEED,           menu_show_speed,        menu_show_main,    PID, IMAGE},
    {"IMAGE",           IMAGE,           menu_show_image,        menu_show_main,    PID, IMAGE},
    // PID
    {"MOTOR_KP",        MOTOR_KP,        menu_set_motor_pid_p,   menu_show_settings,   MOTOR_KP, STEER_KD},
    {"MOTOR_KI",        MOTOR_KI,        menu_set_motor_pid_i,   menu_show_settings,   MOTOR_KP, STEER_KD},
    {"MOTOR_KD",        MOTOR_KD,        menu_set_motor_pid_d,   menu_show_settings,   MOTOR_KP, STEER_KD},
    {"STEER_KP",        STEER_KP,        menu_set_steer_pid_p,   menu_show_settings,   MOTOR_KP, STEER_KD},
    {"STEER_KI",        STEER_KI,        menu_set_steer_pid_i,   menu_show_settings,   MOTOR_KP, STEER_KD},
    {"STEER_KD",        STEER_KD,        menu_set_steer_pid_d,   menu_show_settings,   MOTOR_KP, STEER_KD},
    // SPEED
    {"NORMAL_SPEED",    NORMAL_SPEED,    menu_set_speed_normal,  menu_show_settings,   NORMAL_SPEED, CURVE_SPEED},
    {"CURVE_SPEED",     CURVE_SPEED,     menu_set_speed_curve,   menu_show_settings,   NORMAL_SPEED, CURVE_SPEED},
    // IMAGE
    {"OTSU_K_MIN",      OTSU_K_MIN,      menu_set_otsu_k_min,    menu_show_settings,   OTSU_K_MIN, IMAGE5},
    {"OTSU_K_MAX",      OTSU_K_MAX,      menu_set_otsu_k_max,    menu_show_settings,   OTSU_K_MIN, IMAGE5},
    {"IMAGE3",          IMAGE3,          menu_set_image3,        menu_show_settings,       OTSU_K_MIN, IMAGE5},
    {"IMAGE4" ,         IMAGE4,          menu_set_image4,        menu_show_settings,       OTSU_K_MIN, IMAGE5},
    {"IMAGE5",          IMAGE5,          menu_set_image5,        menu_show_settings,       OTSU_K_MIN, IMAGE5},
};
// const char * menu_names[MENU_ITEM_COUNT] = {
//     // MAIN
//     "START",        "START_WITH_INFO",      "SETTINGS",
//     // SETTINGS
//     "PID",          "SPEED",                "IMAGE",
//     // PID
//     "MOTOR_KP",           "MOTOR_KI",                   "MOTOR_KD",
//     // SPEED
//     "NORMAL_SPEED", "CURVE_SPEED",
//     // IMAGE
//     "OTSU_K_MIN",       "OTSU_K_MAX",        "IMAGE3",   "IMAGE4",   "IMAGE5",
// };

// 测试用
int a;

InfoItem    info_items[MENU_START_WITH_INFO_ITEMS_COUNT] = {
    {L_SPEED,   "L_SPEED",    .value.int_value = &motor_left_pid_calc.current},
    {R_SPEED,   "R_SPEED",    .value.int_value = &motor_right_pid_calc.current},
    {STEER_DUTY,"STEER_DUTY", .value.int_value = (int *)&steerPresentDuty},
    // {ELE,       "ELE",        .value.int_value = &a},
    {L_PID_OUT,"L_PID_OUT", .value.int_value = &motor_left_pid_calc.out},
    {R_PID_OUT,"R_PID_OUT", .value.int_value = &motor_right_pid_calc.out},
    {STEER_PID_OUT,"STEER_PID_OUT", .value.int_value = &steer_pid_calc.out},
    {TIME,"TIME", .value.int_value = &time_per_image},
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

void menu_show_pointer(void){
    screen_show_string(0, (menu_current_index - menu_items[menu_current_index].thisPageStart + 1) * LINE_GAP, ">");
}
// 菜单项目显示函数
void menu_items_show_with_pointer(MenuIndex startIndex,MenuIndex endIndex){
    screen_clear();
    menu_show_pointer();
    screen_show_string(30, 0, "Menu");
    for(int i = startIndex; i <= endIndex; i++){
        screen_show_string(10, (i - startIndex + 1) * LINE_GAP, menu_items[i].name);
    }
}
// 菜单显示函数
void menu_show(void){
    menu_items_show_with_pointer(menu_items[menu_current_index].thisPageStart, menu_items[menu_current_index].thisPageEnd);
}

// 菜单显示函数
void menu_show_main(void){
    menu_current_index = START;
    menu_show();
}
void menu_show_settings(void){
    menu_current_index = PID;
    menu_show();
}
void menu_show_pid(void){
    menu_current_index = MOTOR_KP;
    menu_show();
}
void menu_show_speed(void){
    menu_current_index = NORMAL_SPEED;
    menu_show();
}
void menu_show_image(void){
    menu_current_index = OTSU_K_MIN;
    menu_show();
}

// 车启动类函数
void menu_start(void){
    screen_clear();
    screen_show_string(0, 0, "PRESS ANY KEY TO STOP");
}
void menu_start_with_info(void){
    screen_clear();
    screen_show_string(30, 0, "INFO");
}

// 设置项目函数
void menu_set_int_items(int * items,int per_plus,char * item_name){
    key_all_available();
    screen_clear();
    screen_show_string(0, 0, item_name);
    char str[10];
    while (1)
    {
        if(key_any_pressed){
            if(key_state_get(KEY_INCREASE) == PRESSED){
                *items += per_plus;
                key_state_set(KEY_INCREASE, AVAILABLE);
            }else if(key_state_get(KEY_DECREASE) == PRESSED){
                *items -= per_plus;
                key_state_set(KEY_DECREASE, AVAILABLE);
            }else{
                key_all_available();
                break;
            }
            key_any_pressed = 0;
        }

        sprintf(str, "%9.1f", (float)(*items));
        screen_show_string(0, LINE_GAP, str);
        system_delay_ms(MENU_SET_DALAY);
    }
}

void menu_set_float_items(float * items,float per_plus,char * item_name){
    key_all_available();
    screen_clear();
    screen_show_string(0, 0, item_name);
    char str[10];
    while (1)
    {
        if(key_any_pressed){
            if(key_state_get(KEY_INCREASE) == PRESSED){
                *items += per_plus;
                key_state_set(KEY_INCREASE, AVAILABLE);
            }else if(key_state_get(KEY_DECREASE) == PRESSED){
                *items -= per_plus;
                key_state_set(KEY_DECREASE, AVAILABLE);
            }else{
                key_all_available();
                break;
            }
            key_any_pressed = 0;
        }

        sprintf(str, "%9.1f", (float)(*items));
        screen_show_string(0, LINE_GAP, str);
        system_delay_ms(MENU_SET_DALAY);
    }
}

// =============PID================
void menu_set_motor_pid_p(void){
    menu_set_float_items(&motor_pid_config.KP, MENU_SET_PID_PER_PLUS , "MOTOR_KP");
    menu_show_pid();
}
void menu_set_motor_pid_i(void){
    menu_set_float_items(&motor_pid_config.KI, MENU_SET_PID_PER_PLUS , "MOTOR_KI");
    menu_show_pid();
}
void menu_set_motor_pid_d(void){
    menu_set_float_items(&motor_pid_config.KD, MENU_SET_PID_PER_PLUS , "MOTOR_KD");
    menu_show_pid();
}

void menu_set_steer_pid_p(void){
    menu_set_float_items(&steer_pid_config.KP, MENU_SET_PID_PER_PLUS , "STEER_KP");
    menu_show_pid();
}
void menu_set_steer_pid_i(void){
    menu_set_float_items(&steer_pid_config.KI, MENU_SET_PID_PER_PLUS , "STEER_KI");
    menu_show_pid();
}
void menu_set_steer_pid_d(void){
    menu_set_float_items(&steer_pid_config.KD, MENU_SET_PID_PER_PLUS , "STEER_KD");
    menu_show_pid();
}

// =============SPEED================
void menu_set_speed_normal(void){
    menu_set_int_items(&motor_nomal_speed, MENU_SET_SPEED_PER_PLUS , "NOMAL_SPEED");
    menu_show_speed();
}
void menu_set_speed_curve(void){
    menu_set_int_items(&motor_curve_speed, MENU_SET_SPEED_PER_PLUS , "CURVE_SPEED");
    menu_show_speed();
}

// =============IMAGE================
void menu_set_otsu_k_min(void){
    //menu_set_int_items(&OTSU_K_MIN, MENU_SET_IMAGE_PER_PLUS , "OTSU_K_MIN");
    menu_show_image();
}
void menu_set_otsu_k_max(void){
    //menu_set_int_items(&OTSU_K_MAX, MENU_SET_IMAGE_PER_PLUS , "OTSU_K_MAX");
    menu_show_image();
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
    menu_items_show_with_pointer(menu_items[menu_current_index].thisPageStart, menu_items[menu_current_index].thisPageEnd);
}
void menu_select_last(void){
    if(menu_current_index - 1 < menu_items[menu_current_index].thisPageStart){
        menu_current_index = menu_items[menu_current_index].thisPageEnd;
    }else{
        menu_current_index--;
    }
    menu_items_show_with_pointer(menu_items[menu_current_index].thisPageStart, menu_items[menu_current_index].thisPageEnd);
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
