/*
 * image.h
 *
 *  Created on: 2024年11月23日
 *      Author: lizhi
 */

#ifndef CODE_IMAGE_H_
#define CODE_IMAGE_H_


#include<zf_device_mt9v03x.h>

typedef const uint8 * ImageData;

typedef enum ElementType {
    Normal,
    Cross,
    Island,
} ElementType;

typedef struct ImageResult {
    int8 midline_delta;
    ElementType element_type;
} ImageResult;


ImageResult process_image(ImageData image);

#endif /* CODE_IMAGE_H_ */
