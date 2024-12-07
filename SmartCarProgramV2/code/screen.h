#ifndef _SCREEN_H
#define _SCREEN_H

#include<zf_device_ips200.h>

#define SCREEN_LINK_TYPE IPS200_TYPE_SPI

typedef uint8 *ImageBase;
typedef uint8 *Image[];

typedef enum {
    IMAGE,
    TEXT,
} RenderObjectType;

typedef union {
    char *text;
    ImageBase *image;
} RenderObjectData;

typedef struct {
    RenderObjectType type;
    RenderObjectData data;
} RenderObject;

void screen_init(void);
void screen_show_image(ImageBase image);
void screen_show_object(RenderObject object);

#endif