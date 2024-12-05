#include<cpu0_main.h>

#pragma section all "cpu0_dsram"

uint8 gameFlag = 1;

int core0_main(void)
{
    //逐飞程序保留
    clock_init();                   // 获取时钟频率<务必保留>
    debug_init();                   // 初始化默认调试串口

    //=============================初始化开始==========================
    system_delay_init();
    //if (wireless_uart_init()) printf("无线串口失败！");
    //else printf("无线串口成功！");
    //screen_init();
    steer_init();
    printf("steer_init();！");
    motor_all_init();
    printf("motor_all_init();！");
    system_delay_ms(100);

    encoder_init();
    printf("encoder_init");
    pit_ms_init(CCU60_CH0, 100);
    printf("pit_ms_init(CCU60_CH0, 100);");
    encoder_all_clear();
    pit_ms_init(CCU60_CH1, 100);
    printf("pit_ms_init(CCU60_CH1, 100);");
    //=============================初始化结束==========================
    cpu_wait_event_ready();         // 等待所有核心初始化完毕

    printf("ready!!!");

    while (1) {
        char str[30];
        sprintf(str,"angle:%lf, el:%d\n",angle,element_type);
        wireless_uart_send_string(str);
        system_delay_ms(200);
    }

    return 0;
}

#pragma section all restore
