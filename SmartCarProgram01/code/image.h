#ifndef CODE_IMAGE_H_
#define CODE_IMAGE_H_

#define IMAGE_DEBUG

#ifndef __linux__
	#include<zf_common_typedef.h>
#else
	#define uint8 int
    #define sint8 int
#endif

typedef int (*Image)[188];

typedef enum ElementType {
    Normal,
    Curve,
} ElementType;

void process_image(Image image);

void binarize_image_otsu(Image image);
double search_bound(Image image);

extern ElementType element_type;
extern double angle;

#define PI 3.14159265
#define HEIGHT 120
#define WIDTH 187 // 188 - 1 最右侧有一条黑边
#define MAX_J 186 // 187 - 1
#define PIXELS 22440 // 120 * 187

#endif /* CODE_IMAGE_H_ */
