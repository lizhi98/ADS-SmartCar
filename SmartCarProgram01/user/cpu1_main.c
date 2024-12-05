#include "zf_common_headfile.h"
#include"image.h"


#pragma section all "cpu1_dsram"
// 将本语句与#pragma section all restore语句之间的全局变量都放在CPU1的RAM中

// **************************** 代码区域 ****************************

// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设

extern uint8 gameFlag;
extern int8 steerSetAngle;
extern int16 motorLeftSetSpeed;
extern int16 motorRightSetSpeed;
extern double angle;
extern ElementType element_type;

void core1_main(void)
{
    disable_Watchdog();                     // 关闭看门狗
    interrupt_global_enable(0);             // 打开全局中断
    // 此处编写用户代码 例如外设初始化代码等

    // 此处编写用户代码 例如外设初始化代码等
    cpu_wait_event_ready();                 // 等待所有核心初始化完毕
    mt9v03x_init();
    //等待开始发车
    while (gameFlag != 1);
    
    uint8 image_copy[MT9V03X_H][MT9V03X_W];

#ifdef IMAGE_DEBUG
    seekfree_assistant_interface_init(SEEKFREE_ASSISTANT_DEBUG_UART);
    seekfree_assistant_camera_information_config(SEEKFREE_ASSISTANT_MT9V03X, image_copy[0], MT9V03X_W, MT9V03X_H);
#endif

    while (1) {
        if (mt9v03x_finish_flag) {
#ifdef IMAGE_DEBUG
            memcpy(image_copy[0], mt9v03x_image[0], MT9V03X_IMAGE_SIZE);
            process_image(image_copy);
            seekfree_assistant_camera_send();
#endif
            mt9v03x_finish_flag = 0;
            steerSetAngle = angle;
            if(element_type == Normal){
                motorLeftSetSpeed = 3000;
                motorRightSetSpeed = 3000;
            }
            else if(element_type == Curve){
                motorLeftSetSpeed = 2000;
                motorRightSetSpeed = 2000;
            }
        }
        if (gameFlag == 0){
            motorLeftSetSpeed = 0;
            motorRightSetSpeed = 0;
            break;
        }
    }


}
#pragma section all restore
// **************************** 代码区域 ****************************
