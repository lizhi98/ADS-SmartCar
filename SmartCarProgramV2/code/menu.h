#ifndef CODE_MENU2_H
#define CODE_MENU2_H

#include "screen.h"
#include "key.h"


#define LINE_GAP 15

#define MENU_ITEM_COUNT 19

#define MENU_SET_DALAY 100

#define MENU_SET_PID_PER_PLUS 0.2f
#define MENU_SET_SPEED_PER_PLUS 10u
#define MENU_SET_IMAGE_PER_PLUS 1u

// 第一个调节页面菜单索引
// #define MENU_SETTING_PAGE_START_MENU_ITEM_INDEX MOTOR_KP
#define MENU_START_WITH_INFO_ITEMS_COUNT 7
#define MENU_START_WITH_INFO_ITEMS_LAST_INT STEER_DUTY

typedef enum _InfoIndex{
    L_SPEED,
    R_SPEED,
    STEER_DUTY,
    L_PID_OUT,
    R_PID_OUT,
    STEER_PID_OUT,
    TIME,
} InfoIndex;

typedef enum _MenuIndex{
    // MAIN
    START,              START_WITH_INFO,    SETTINGS,
    // SETTINGS
    PID,                SPEED,              IMAGE,
    // PID
    MOTOR_KP,           MOTOR_KI,           MOTOR_KD,
    STEER_KP,           STEER_KI,           STEER_KD,
    // SPEED
    NORMAL_SPEED,       CURVE_SPEED,
    // IMAGE
    OTSU_K_MIN,         OTSU_K_MAX,         IMAGE3,         IMAGE4,         IMAGE5,
} MenuIndex;

typedef struct _MenuItem {
    char *      name;
    MenuIndex   index;
    void        (*next)(void);
    void        (*back)(void);
    MenuIndex   thisPageStart;
    MenuIndex   thisPageEnd;
} MenuItem;

typedef struct _InfoItem{
    InfoIndex   index;
    char*       name;
    union InfoValue {
        int*    int_value;
        float*  float_value;
    } value;
    
} InfoItem;

extern MenuIndex    menu_current_index;
extern MenuItem     menu_items[MENU_ITEM_COUNT];
extern InfoItem     info_items[MENU_START_WITH_INFO_ITEMS_COUNT];

void menu_show_pointer(void);
void menu_items_show_with_pointer(MenuIndex startIndex, MenuIndex endIndex);

// 菜单显示函数
void menu_show_main(void);
void menu_show_settings(void);
void menu_show_pid(void);
void menu_show_speed(void);
void menu_show_image(void);

// 车启动类函数
void menu_start(void);
void menu_start_with_info(void);

// 设置项目函数
void menu_set_motor_pid_p(void);
void menu_set_motor_pid_i(void);
void menu_set_motor_pid_d(void);

void menu_set_steer_pid_p(void);
void menu_set_steer_pid_i(void);
void menu_set_steer_pid_d(void);

void menu_set_speed_normal(void);
void menu_set_speed_curve(void);

void menu_set_otsu_k_min(void);
void menu_set_otsu_k_max(void);
void menu_set_image3(void);
void menu_set_image4(void);
void menu_set_image5(void);

// 调用执行函数
void menu_select_next(void);
void menu_select_last(void);
void menu_ok(void);
void menu_back(void);

void menu_init(void);

#endif
