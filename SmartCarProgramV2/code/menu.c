#include"menu.h"

//屏幕选项指针位置 1-10 分别为第几行,默认为第一行
static Location     pointerLine = 1;    //默认为第一行
static Pages        currentPage = PAGE_MAIN; //默认为主菜单
static OptionIndex  currentChoice      = 0;    //默认为一个不存在的索引
static uint8        wrongFlag   = 0;
void show_main_menu(void){
    ips200_show_string(100, LINE_GAP*MENU_LINE,                 "MENU");
    ips200_show_string(10,  LINE_GAP*GO_LINE,                   "GO");
    ips200_show_string(10,  LINE_GAP*GO_AND_SHOW_CONFIG_LINE,   "GO_AND_SHOW_CONFIG");
    ips200_show_string(10,  LINE_GAP*SPEED_LINE,                "SPEED");
    ips200_show_string(10,  LINE_GAP*PID_LINE,                  "PID");
    ips200_show_string(0,   LINE_GAP*pointerLine,               "->");
}
void show_speed_menu(void){
    ips200_show_string(100, LINE_GAP*MENU_LINE,                 "MENU");
    ips200_show_string(10,  LINE_GAP*BACK_LINE,                 "BACK");
    ips200_show_string(10,  LINE_GAP*MOTOR_SPEED_K_LINE,        "speed_K");
    ips200_show_string(10,  LINE_GAP*NORMOL_SPEED_LINE,         "NormolSpeedRaw");
    ips200_show_string(10,  LINE_GAP*CURVE_SPEED_LINE,          "CurveSpeedRaw");
    ips200_show_string(0,   LINE_GAP*pointerLine,               "->");
}
void show_pid_menu(void){
    ips200_show_string(100, LINE_GAP*MENU_LINE,                 "MENU");
    ips200_show_string(10,  LINE_GAP*BACK_LINE,                 "BACK");
    ips200_show_string(10,  LINE_GAP*KP_LINE,                   "KP");
    ips200_show_string(10,  LINE_GAP*KI_LINE,                   "KI");
    ips200_show_string(10,  LINE_GAP*KD_LINE,                   "KD");
    ips200_show_string(0,   LINE_GAP*pointerLine,               "->");
}

void menu_update(void){
    if (wrongFlag ==1) return;
    
    screen_clear();
    switch (currentPage)
    {
    case PAGE_MAIN:
        show_main_menu();
        break;
    case PAGE_SPEED_CONFIG:
        show_speed_menu();
        break;
    case PAGE_PID_CONFIG:
        show_pid_menu();
        break;
    default:
        wrongFlag = 1;
        screen_wrong();
        break;
    }
}

void menu_jump(Pages target){
    if (wrongFlag ==1) return;
    
    switch (target)
    {
    case PAGE_MAIN:
        pointerLine = GO_LINE;
        currentChoice      = GO;
        currentPage = PAGE_MAIN;
        break;
    case SPEED:
        pointerLine = BACK_LINE;
        currentChoice      = BACK;
        currentPage = PAGE_SPEED_CONFIG;
    case PID:
        pointerLine = BACK_LINE;
        currentChoice      = BACK;
        currentPage = PAGE_PID_CONFIG;
    default:
        wrongFlag = 1;
        screen_wrong();
        break;
    }
    menu_update();
    
}

void edit_config(keyIndex key){
    if (wrongFlag ==1) return;
    
    switch (currentChoice)
    {
    case MOTOR_SPEED_K:
        if(key == INCREASE) ; 
        if(key == DECREASE) ;
        break;
    case NORMOL_SPEED_RAW:
        //这里写调节直道速度
        if(key == INCREASE) ; 
        if(key == DECREASE) ;
        break;
    case CURVE_SPEED_RAW:
        if(key == INCREASE) ; 
        if(key == DECREASE) ;
        break;
    case KP:
        if(key == INCREASE) ; 
        if(key == DECREASE) ;
        break;
    case KI:
        if(key == INCREASE) ; 
        if(key == DECREASE) ;
        break;
    case KD:
        if(key == INCREASE) ; 
        if(key == DECREASE) ;
        break;
    default:
        wrongFlag = 1;
        screen_wrong();
        break;
    }
    menu_update();
}

void key_control(keyIndex key){
    switch (key)
    {
    case OK:
            switch (currentChoice)
            {
            case BACK:
                menu_jump(PAGE_MAIN);
                break;
            case SPEED:
                menu_jump(PAGE_SPEED_CONFIG);
                break;
            case PID:
                menu_jump(PAGE_PID_CONFIG);
                break;
            default:
                // screen_wrong();
                //由于可能会误触了确定键，所以此处不再报错，使用时小心一些
                break;
            }
            break;
    case INCREASE:
    case DECREASE:
        edit_config(key);
        break;
    case DOWN:
            if (currentChoice == PID||
                currentChoice ==CURVE_SPEED_RAW||
                currentChoice==KD)
            {
                menu_jump(currentPage);
            }else
            {
                currentChoice ++;
                pointerLine ++;
                menu_update();
            }
    default:
        screen_wrong();
        break;
    }
}
