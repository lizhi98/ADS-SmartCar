#include "zf_common_headfile.h"
#include"image.h"
#include<string.h>

//#define WIFISPI

#pragma section all "cpu1_dsram"
// 将本语句与#pragma section all restore语句之间的全局变量都放在CPU1的RAM中

// **************************** 代码区域 ****************************

// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设

extern int8 steerSetAngle;
extern int16 motorLeftSetSpeed;
extern int16 motorRightSetSpeed;
extern double angle;
extern ElementType element_type;
//extern struct MotorPIDConfig left,right;

void core1_main(void)
{
    disable_Watchdog();                     // 关闭看门狗
    interrupt_global_enable(0);             // 打开全局中断
    // 此处编写用户代码 例如外设初始化代码等

    // 此处编写用户代码 例如外设初始化代码等
    cpu_wait_event_ready();                 // 等待所有核心初始化完毕

#ifdef WIFISPI
    //WiFiSPI初始化
    wifi_spi_init("AP-lizhi", "9894653xxk");

    while(wifi_spi_socket_connect(                                          // 向指定目标 IP 的端口建立 TCP 连接
        "TCP",                                                              // 指定使用TCP方式通讯
        WIFI_SPI_TARGET_IP,                                                 // 指定远端的IP地址，填写上位机的IP地址
        WIFI_SPI_TARGET_PORT,                                               // 指定远端的端口号，填写上位机的端口号，通常上位机默认是8080
        WIFI_SPI_LOCAL_PORT))                                               // 指定本机的端口号
    {
        // 如果一直建立失败 考虑一下是不是没有接硬件复位
        printf("\r\n Connect TCP Servers error, try again.");
        system_delay_ms(100);                                               // 建立连接失败 等待 100ms
    }

#endif

    mt9v03x_init();
    //启动计时
    system_start();
    //等待开始发车

#ifdef IMAGE_DEBUG
    uint8 image_copy[MT9V03X_H][MT9V03X_W];
    seekfree_assistant_interface_init(SEEKFREE_ASSISTANT_DEBUG_UART);
    seekfree_assistant_camera_information_config(SEEKFREE_ASSISTANT_MT9V03X, image_copy[0], MT9V03X_W, MT9V03X_H);
#endif

    uint32 timeS;

    while (1) {
        if (mt9v03x_finish_flag) {
            timeS = system_getval_ms();
#ifdef IMAGE_DEBUG
            memcpy(image_copy[0], mt9v03x_image[0], MT9V03X_IMAGE_SIZE);
            process_image(image_copy);
            seekfree_assistant_camera_send();
#else
            process_image(mt9v03x_image);
#endif

            char str[15];
            sprintf(str,"time:%lu\n",(system_getval_ms() - timeS));

            // wireless_uart_send_string(str);
#ifdef WIFISPI
            uint8 * p = (uint8 *)str;
            wifi_spi_send_buffer(p, strlen(str));
#endif

            printf(str);

            mt9v03x_finish_flag = 0;

    while(1){
        if(mt9v03x_finish_flag){
            process_image(mt9v03x_image);
            steerSetAngle = angle;
            //steer.target = angle;
            if(element_type == Normal){
                motorLeftSetSpeed = 3500;
                motorRightSetSpeed = 3500;
            }
            else if(element_type == Curve){
                motorLeftSetSpeed = 3000;
                motorRightSetSpeed = 3000;
            }
        }
        }
    }


    }}
#pragma section all restore
// **************************** 代码区域 ****************************


