#include "zf_common_headfile.h"

extern uint8 run_flag;
#include "motor.h"
#include "pid.h"
#pragma section all "cpu1_dsram"
// 将本语句与#pragma section all restore语句之间的全局变量都放在CPU1的RAM中

// **************************** 代码区域 ****************************

// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设

void core1_main(void)
{
    disable_Watchdog();                     // 关闭看门狗
    interrupt_global_enable(0);             // 打开全局中断
    // 此处编写用户代码 例如外设初始化代码等



    // 此处编写用户代码 例如外设初始化代码等
    cpu_wait_event_ready();                 // 等待所有核心初始化完毕

    uint8 delay_time_need_flag = 1;
    while (TRUE)
    {
        // 此处编写需要循环执行的代码
        system_delay_ms(100);
        if (run_flag)
        {
            if(delay_time_need_flag){
                pid_set_motor_target(motor_nomal_speed);
                system_delay_ms(1000);
                motor_start();
                pid_start_calc();
                delay_time_need_flag = 0;
            }
        }else
        {
            motor_make_unpower();
            pid_stop_calc_and_clear();
            delay_time_need_flag = 1;
        }

        // 此处编写需要循环执行的代码
    }
}
#pragma section all restore
// **************************** 代码区域 ****************************
