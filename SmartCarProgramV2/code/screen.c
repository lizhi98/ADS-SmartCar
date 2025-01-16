#include "screen.h"

void screen_init() {
    ips200_init(SCREEN_LINK_TYPE);
    ips200_full(RGB565_BLACK);
}
void screen_clear(void){
    // ips200_clear();
    ips200_full(RGB565_BLACK);
}

