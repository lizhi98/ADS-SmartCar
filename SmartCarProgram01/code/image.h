#ifndef CODE_IMAGE_H_
#define CODE_IMAGE_H_

typedef const uint8 * ImageData;

typedef enum ElementType {
    Normal,
    Curve,
    Cross,
    Island,
} ElementType;

ElementType element_type;

typedef struct ImageResult {
    int8 midline_delta;
    ElementType element_type;
} ImageResult;

ImageResult process_image(ImageData image);

void binarize_image(ImageData image);

#endif /* CODE_IMAGE_H_ */
