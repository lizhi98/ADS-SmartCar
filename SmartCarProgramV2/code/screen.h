#ifndef _CODE_SCREEN_H
#define _CODE_SCREEN_H

#include <zf_device_ips200.h>
#include <zf_device_mt9v03x.h>
#include <zf_common_font.h>

#define SCREEN_LINK_TYPE IPS200_TYPE_SPI

#define screen_show_string(x, y, str)           (ips200_show_string(x, y, str))
#define screen_show_int(x, y, integer, count)   (ips200_show_int(x, y, integer, count))
#define screen_show_image(image)                (ips200_displayimage03x(image, MT9V03X_W, MT9V03X_H))

typedef uint8 * ImageBase;
typedef uint8 * Image[];

void screen_init(void);
void screen_clear(void);

#endif
