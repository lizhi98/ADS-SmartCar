/*
 * camera.c
 *
 *  Created on: 2024年11月23日
 *      Author: lizhi
 */

#include "camera.h"

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

ImageResult process_image(ImageData image) {
    ImageResult result;

    result.midline_delta = 0;
    result.element_type = Normal;

    return result;
}
