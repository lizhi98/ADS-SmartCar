#ifndef _CODE_SCREEN_H
#define _CODE_SCREEN_H

#include<zf_device_ips200.h>

#define ON  1
#define OFF 0
#define SCREEN_LINK_TYPE IPS200_TYPE_SPI

#define SWITCH_IMAGE                ON
#define SWITCH_IMAGE_PROCESS_TIME   ON
#define SWITCH_ANGLE                ON
#define SWITCH_ELEMENT_TYPE         ON
#define SWITCH_MOTOR_LEFT_SPEED     ON
#define SWICTH_MOTOR_RIGHT_SPEED    ON

typedef uint8 *ImageBase;
typedef uint8 *Image[];
typedef char  *text;

// typedef enum {
//     IMAGE,
//     TEXT,
// } RenderObjectType;

// typedef union {
//     char *text;
//     ImageBase *image;
// } RenderObjectData;

// typedef struct {
//     RenderObjectType type;
//     RenderObjectData data;
// } RenderObject;

typedef struct _ObjectData{
    ImageBase image;
    uint16 imageProcessTime;
    uint8 elementType;
    double angle;
    int16 leftMotorS;
    int16 rightMotorS;
} ObjectData;

extern ObjectData objectData;

void screen_init(void);
void screen_clear(void);
void screen_show_image(ImageBase image);
//留出图像位置
void screen_show_text(text);

void screen_show_menu(void);
void screen_show_objects(void);
void screen_wrong(void);

#endif
