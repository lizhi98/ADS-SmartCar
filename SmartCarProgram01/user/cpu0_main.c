#include<cpu0_main.h>

#pragma section all "cpu0_dsram"
// 将本语句与#pragma section all restore语句之间的全局变量都放在CPU0的RAM中

// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设
uint8 gameFlag = 1;
// **************************** 代码区域 ****************************
int core0_main(void)
{
    //逐飞程序保留
    clock_init();                   // 获取时钟频率<务必保留>
    debug_init();                   // 初始化默认调试串口

    //=============================初始化S==========================
    system_delay_init();
    if(wireless_uart_init()){
        printf("无线串口失败！");
    }
    printf("无线串口成功！");
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
    //=============================初始化E==========================
    cpu_wait_event_ready();         // 等待所有核心初始化完毕

    printf("ready!!!");

    while(1){
        char str[30];
        sprintf(str,"left:%d,right:%d\n",motorLeftSpeed,motorRightSpeed);
        wireless_uart_send_string(str);
        //printf(str);
        sprintf(str,"leftSet:%d,rightSet:%d\n",motorLeftSetSpeed,motorRightSetSpeed);
        wireless_uart_send_string(str);
        //printf(str);
        system_delay_ms(100);
    }


    return 0;
}


#pragma section all restore
// **************************** 代码区域 ****************************
