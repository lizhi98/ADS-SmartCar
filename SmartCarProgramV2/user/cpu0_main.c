#include "zf_common_headfile.h"
#include "screen.h"
#include "key.h"
#include "menu.h"
#include "pid.h"

uint8 run_flag = FALSE;

#pragma section all "cpu0_dsram"

// 将本语句与#pragma section all restore语句之间的全局变量都放在CPU0的RAM中
int core0_main(void)
{
    clock_init();                   // 获取时钟频率<务必保留>
    debug_init();                   // 初始化默认调试串口
    // ===========外设初始化============
    system_delay_init();
    screen_init();
    key_init_();
    // 此处编写用户代码 例如外设初始化代码等
    cpu_wait_event_ready();         // 等待所有核心初始化完毕

MENU:
    // 菜单初始化
    menu_init();
    // 按键复原
    key_all_available();
    while (TRUE)
    {
        // 此处编写需要循环执行的代码

        // 菜单程序
        // 程序刚开始执行时为主菜单
        // 判断是否有按键按下
        if (key_any_pressed)
        {   
            if(key_state_get(KEY_OK) == PRESSED)
            {
                if (menu_items[menu_current_index].index == START)
                {
                    key_state_set(KEY_OK, AVAILABLE);
                    goto MENU_START;
                }else if(menu_items[menu_current_index].index == START_WITH_INFO)
                {
                    key_state_set(KEY_OK, AVAILABLE);
                    goto MENU_START_WITH_INFO;
                }
                menu_ok();
                key_state_set(KEY_OK, AVAILABLE);
            }else if(key_state_get(KEY_BACK) == PRESSED){
                menu_back();
                key_state_set(KEY_BACK, AVAILABLE);
            }else if(key_state_get(KEY_INCREASE) == PRESSED){
                menu_select_next();
                key_state_set(KEY_INCREASE, AVAILABLE);
            }else if(key_state_get(KEY_DECREASE) == PRESSED){
                menu_select_last();
                key_state_set(KEY_DECREASE, AVAILABLE);
            }
            key_any_pressed = 0;
        }
    }

MENU_START:
    // 车启动菜单
    menu_start();
    // 车启动
    run_flag = TRUE;
    key_any_pressed = 0;
    while (TRUE)
    {   // 判断是否有返回操作
        // 延迟10ms防止定时中断和CPU1的程序争抢key_any_pressed
        system_delay_ms(10);
        if(key_any_pressed)
        {
            run_flag = FALSE;
            goto MENU;
        }
    }

MENU_START_WITH_INFO:
    // 车启动菜单
    menu_start_with_info();
    // 车启动
    run_flag = TRUE;
    key_any_pressed = 0;
    // 延迟10ms防止定时中断和CPU1的程序争抢key_any_pressed
    system_delay_ms(10);
    while (TRUE)
    {   // 判断是否有返回操作
        if(key_any_pressed)
        {
            run_flag = FALSE;
            goto MENU;
        }
    }
}


#pragma section all restore
