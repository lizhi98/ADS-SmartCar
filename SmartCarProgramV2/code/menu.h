#ifndef CODE_MENU2_H
#define CODE_MENU2_H

#include "screen.h"

#define LINE_GAP 15

#define MENU_ITEM_COUNT 16
// 第一个调节页面菜单索引
#define MENU_SETTING_PAGE_START_MENU_ITEM_INDEX KP



typedef enum _MenuIndex{
    // MAIN
    START,              START_WITH_INFO ,   SETTINGS,
    // SETTINGS
    PID,                SPEED,              IMAGE,
    // PID
    KP,                 KI,                 KD,
    // SPEED
    NORMAL_SPEED,       CURVE_SPEED,
    // IMAGE
    IMAGE1,             IMAGE2,             IMAGE3,        IMAGE4,      IMAGE5,
} MenuIndex;

typedef struct _MenuItem{
    MenuIndex   index;
    void        (*next)(void);
    void        (*back)(void);
    MenuIndex   thisPageStart;
    MenuIndex   thisPageEnd;
} MenuItem;

extern  MenuIndex   menu_current_index;
extern  MenuItem    menu_items[MENU_ITEM_COUNT];

void menu_next_item(MenuItem item);
void menu_last_item(MenuItem item);


void menu_show_pointer(void);
void menu_show(MenuIndex startIndex,MenuIndex endIndex);
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
void menu_set_pid_p(void);
void menu_set_pid_i(void);
void menu_set_pid_d(void);

void menu_set_speed_normal(void);
void menu_set_speed_curve(void);

void menu_set_image1(void);
void menu_set_image2(void);
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