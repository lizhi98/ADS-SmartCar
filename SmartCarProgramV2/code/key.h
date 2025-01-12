#ifndef CODE_KEY_H_
#define CODE_KEY_H_

#include<zf_driver_gpio.h>

#define key_count 4

#define KEY_RELEASED_LEVEL  GPIO_HIGH
#define KEY_PRESSED_LEVEL   GPIO_LOW

#define KEY_DECREASE_PIN    P20_6   // 一般用于减小数值
#define KEY_INCREASE_PIN    P20_7   // 一般用于增加数值
#define KEY_DOWN_PIN        P11_2   // 一般用于调到下一个选项
#define KEY_OK_PIN          P11_3   // 一般用于确认

#define KEY_SCAN_INTERVAL   10      // 按键扫描间隔（ms）
#define KEY_PRESS_TIME      100     // 按键按下时间（ms）

// 按键状态
typedef enum _key_state{
    AVAILABLE,
    PRESSED,
} key_state;
// 按键的索引（用于结构体数组中区分）
typedef enum _key_index{
    KEY_DECREASE,
    KEY_INCREASE,
    KEY_DOWN,
    KEY_OK,
} key_index;
//按键结构体
typedef struct key{
        gpio_pin_enum   gpio_pin;
        key_state       state;
        uint16          press_time_count;
} key;

void key_init_(void);
void key_all_scan(void);
key_state key_state_get(key_index index);
void key_state_set(key_index index, key_state state);
#endif
