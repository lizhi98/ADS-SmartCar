#ifndef CODE_IMAGE_H_
#define CODE_IMAGE_H_

#include<zf_common_typedef.h>
typedef const uint8 * ImageData;

typedef uint8 (*Image)[188];

typedef enum ElementType {
    Normal,
    Curve,
    Cross,
    Island,
} ElementType;

typedef struct ImageResult {
    int8 midline_delta;
    ElementType element_type;
} ImageResult;

ImageResult process_image(Image image);

void binarize_image(Image image);

#endif /* CODE_IMAGE_H_ */
