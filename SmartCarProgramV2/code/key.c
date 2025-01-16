#include"key.h"

static key keys[key_count];

uint8 key_any_pressed = 0;

// 按键初始化
void key_init_(void){
    // 初始化结构体
    keys[KEY_DECREASE].gpio_pin = KEY_DECREASE_PIN;
    keys[KEY_INCREASE].gpio_pin = KEY_INCREASE_PIN;
    keys[KEY_BACK].gpio_pin = KEY_BACK_PIN;
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
    pit_ms_init(KEY_PIT_CH, KEY_SCAN_INTERVAL);
}

void key_all_available(void){
    key_any_pressed = 0;
    for (size_t i = 0; i < key_count; i++)
    {
        keys[i].state = AVAILABLE;
        keys[i].press_time_count = 0;
    }
}

// 按键扫描
void key_all_scan(void){
    // 如果有按键按下则不再扫描
    if(key_any_pressed){
        return;
    }
    for (size_t i = 0; i < key_count; i++)
    {
        if(gpio_get_level(keys[i].gpio_pin) == KEY_PRESSED_LEVEL){
            keys[i].press_time_count ++;
        }else{
            if(keys[i].state != PRESSED && 
               keys[i].press_time_count * KEY_SCAN_INTERVAL >= KEY_PRESS_TIME)
            {
                key_any_pressed = 1;
                keys[i].state = PRESSED;
            }
            keys[i].press_time_count = 0;
        }
    }
}
keyState key_state_get(keyIndex index){
    return keys[index].state;
}
void key_state_set(keyIndex index, keyState state){
    keys[index].state = state;
}
