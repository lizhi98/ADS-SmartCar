#include "screen.h"
#include <zf_device_mt9v03x.h>

void screen_init() {
    ips200_init(SCREEN_LINK_TYPE);
}


void screen_show_image(ImageBase image) {
    ips200_displayimage03x(image,MT9V03X_W,MT9V03X_H);
}

void screen_show_object(RenderObject *object) {
    RenderObjectData data = object->data;
    switch (object->type)
    {
    case TEXT:
        ips200_show_string(0, MT9V03X_H + 5, data.text);
        break;
    case IMAGE:
        ips200_show_gray_image(0, 0, data.image, MT9V03X_W, MT9V03X_H, MT9V03X_W, MT9V03X_H, 0);
        break;
    }
}

void test_screen_show_config() {
    RenderObject object = { TEXT, { "test" } };
    screen_show_object(&object);
}