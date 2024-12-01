/*
 * camera.c
 *
 *  Created on: 2024年11月23日
 *      Author: lizhi
 */

#include "image.h"



void init_image_sending() {
    seekfree_assistant_camera_boundary_config();
}

ImageResult process_image(ImageData image) {
    ImageResult result;

    result.midline_delta = 0;
    result.element_type = Normal;

    return result;
}
