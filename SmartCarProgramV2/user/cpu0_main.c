#include "zf_common_headfile.h"
#include "screen.h"
#include "key.h"
#pragma section all "cpu0_dsram"
// 将本语句与#pragma section all restore语句之间的全局变量都放在CPU0的RAM中

// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设

// **************************** 代码区域 ****************************
int core0_main(void)
{
    clock_init();                   // 获取时钟频率<务必保留>
    debug_init();                   // 初始化默认调试串口
    // 此处编写用户代码 例如外设初始化代码等
    system_delay_init();
    screen_init();
    key_init_();
    pit_ms_init(CCU61_CH1, KEY_SCAN_INTERVAL);
    //pit_start(CCU61_CH1);
    // 此处编写用户代码 例如外设初始化代码等
    cpu_wait_event_ready();         // 等待所有核心初始化完毕
    uint32 count[4] = {0};
    char str_temp[20];
    while (TRUE)
    {
        // 此处编写需要循环执行的代码

        if (key_state_get(KEY_DECREASE) == PRESSED)
        {
            sprintf(str_temp, "decrease %d", count[0]++);
            ips200_show_string(0, 0, str_temp);
            key_state_set(KEY_DECREASE, AVAILABLE);
        }
        if (key_state_get(KEY_INCREASE) == PRESSED)
        {
            sprintf(str_temp, "increase %d", count[1]++);
            ips200_show_string(0, 20, str_temp);
            key_state_set(KEY_INCREASE, AVAILABLE);
        }
        if (key_state_get(KEY_DOWN) == PRESSED)
        {
            sprintf(str_temp, "down %d", count[2]++);
            ips200_show_string(0, 40, str_temp);
            key_state_set(KEY_DOWN, AVAILABLE);
        }
        if (key_state_get(KEY_OK) == PRESSED)
        {
            sprintf(str_temp, "ok %d", count[3]++);
            ips200_show_string(0, 60, str_temp);
            key_state_set(KEY_OK, AVAILABLE);
        }
        

        // 此处编写需要循环执行的代码
    }
}

#pragma section all restore
// **************************** 代码区域 ****************************
