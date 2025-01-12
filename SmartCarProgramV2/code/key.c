#include"key.h"

static key keys[key_count];

// 按键初始化
void key_init_(void){
    // 初始化结构体
    keys[KEY_DECREASE].gpio_pin = KEY_DECREASE_PIN;
    keys[KEY_INCREASE].gpio_pin = KEY_INCREASE_PIN;
    keys[KEY_DOWN].gpio_pin = KEY_DOWN_PIN;
    keys[KEY_OK].gpio_pin = KEY_OK_PIN;
    for (size_t i = 0; i < key_count; i++)
    {
        keys[i].state = AVAILABLE;
        keys[i].press_time_count = 0;
    }
    
    // 初始化GPIO
    for (size_t i = 0; i < key_count; i++)
    {
        gpio_init(keys[i].gpio_pin, GPI, GPIO_HIGH, GPI_PULL_UP);
    }
    
}

// 按键扫描
void key_all_scan(void){
    for (size_t i = 0; i < key_count; i++)
    {
        if(gpio_get_level(keys[i].gpio_pin) == KEY_PRESSED_LEVEL){
            keys[i].press_time_count ++;
        }else{
            if(keys[i].state != PRESSED && 
               keys[i].press_time_count * KEY_SCAN_INTERVAL >= KEY_PRESS_TIME)
            {
                keys[i].state = PRESSED;
            }
            keys[i].press_time_count = 0;
        }
    }
}
key_state key_state_get(key_index index){
    return keys[index].state;
}
void key_state_set(key_index index, key_state state){
    keys[index].state = state;
}
