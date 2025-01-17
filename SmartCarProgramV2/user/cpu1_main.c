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
    uint32 timeTemp;
    uint8 delay_time_need_flag = 1;
    uint8 runed_flag = 0;
    while (TRUE)
    {
        // 此处编写需要循环执行的代码
        if (run_flag)
        {   
            runed_flag = 1;
            if(delay_time_need_flag){
                pid_set_motor_target(motor_normal_speed);
                system_delay_ms(1000);
                motor_start();
                pid_start_calc();

                delay_time_need_flag = 0;
            }

            if(mt9v03x_finish_flag && !image_process_finish){
                timeTemp = system_getval_ms();
                process_image(mt9v03x_image);
                time_per_image = system_getval_ms() - timeTemp;
                image_process_finish = 1;
            }
            
        }else
        {
            motor_make_unpower();
            if(runed_flag){
                pid_stop_calc_and_clear();
                runed_flag = 0;
            }
            delay_time_need_flag = 1;
        }

        // 此处编写需要循环执行的代码
    }
}
#pragma section all restore
// **************************** 代码区域 ****************************
