#include<cpu0_main.h>

#pragma section all "cpu0_dsram"


int core0_main(void)
{
    //逐飞程序保留
    clock_init();                   // 获取时钟频率<务必保留>
    debug_init();                   // 初始化默认调试串口

    //=============================初始化开始==========================
    system_delay_init();
    wireless_uart_init();
    //screen_init();
    steer_init();

    motor_all_init();

    system_delay_ms(100);

    encoder_init();

    pit_ms_init(CCU60_CH0, 100);
    encoder_all_clear();
    pit_ms_init(CCU60_CH1, 100);

    //=============================初始化结束==========================
    cpu_wait_event_ready();         // 等待所有核心初始化完毕

    while (1) {
        char str[30];
        sprintf(str,"angle:%lf, el:%d\n",angle,element_type);
        printf(str);
        system_delay_ms(500);
    }

    return 0;
}

#pragma section all restore
