#include "zf_common_headfile.h"

extern uint8 run_flag;
uint32 time_per_image;
uint8 image_process_finish=0;
#include "motor.h"
#include "menu.h"
#include "pid.h"
#include "image.h"
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
    mt9v03x_init();
    system_start();
    uint32 time_start;
    uint8 delay_time_need_flag = 1;
    uint8 has_run_flag = 0;
    uint8 rapid_clock = 500;
    while (TRUE)
    {
        // 此处编写需要循环执行的代码
        if (run_flag) {   
            has_run_flag = 1;
            if (delay_time_need_flag) {
                pid_set_motor_target(motor_normal_speed);
                system_delay_ms(1000);
                motor_start();
                pid_start_calc();

                delay_time_need_flag = 0;
            }

            if (rapid_clock) {
                pid_set_motor_target((-- rapid_clock ? 1.5 : 1) * motor_normal_speed);
            }
            

            if (mt9v03x_finish_flag && !image_process_finish) {
                time_start = system_getval_ms();
                process_image(mt9v03x_image);
                time_per_image = system_getval_ms() - time_start;
                if (search_result.element_type == Zebra) run_flag = 0;
                image_process_finish = 1;
            }
            
        }
        else {
            motor_make_unpower();
            if (has_run_flag) {  // 注意和上面的run_flag区分
                pid_stop_calc_and_clear();
                has_run_flag = 0;
            }
            delay_time_need_flag = 1;
        }

        // 此处编写需要循环执行的代码
    }
}
#pragma section all restore
// **************************** 代码区域 ****************************
