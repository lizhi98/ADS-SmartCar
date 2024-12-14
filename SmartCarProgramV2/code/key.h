#ifndef CODE_KEY_H_
#define CODE_KEY_H_

#include<zf_driver_gpio.h>

#define KEY_LEFT_PIN    P20_6   // 一般用于减小数值
#define KEY_RIGHT_PIN   P20_7   // 一般用于增加数值
#define KEY_DOWN_PIN    P11_2   // 一般用于调到下一个选项
#define KEY_OK_PIN      P11_3   // 一般用于确认

typedef enum{
    DECREASE, INCREASE,   DOWN,   OK,
}KeyIndex;

void key_init_(void);
void key_close(void);

#endif
