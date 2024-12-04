#ifndef CODE_IMAGE_H_
#define CODE_IMAGE_H_

#ifndef __linux__
	#include<zf_common_typedef.h>
#else
	#define uint8 int
#endif

typedef uint8 (*Image)[188];

typedef enum ElementType {
    Normal,
    Curve,
} ElementType;

void process_image(Image image);

void binarize_image_otsu(Image image);
double search_bound(Image image);

#define HEIGHT 120
#define WIDTH 188
#define PIXELS 22560 // 120 * 188

#endif /* CODE_IMAGE_H_ */
