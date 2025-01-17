#ifndef CODE_IMAGE_H_
#define CODE_IMAGE_H_

#ifndef __linux__
	#include<zf_common_typedef.h>
#else
	#define uint8 unsigned char
    #define int8 char
#endif

#ifndef PI
#define PI 3.14159265
#endif
#define HEIGHT 120
#define REAL_WIDTH 188
#define WIDTH 187
#define MID_X 93
#define MAX_X 186
#define MAX_Y 119

typedef uint8 (*Image)[REAL_WIDTH];

typedef enum ElementType_t {
    Normal,
    Curve,
} ElementType;

typedef enum Track_t {
    Left,
    Right,
    Both,
} Track;

typedef struct MidlineResult_t {
    float offset;
#ifdef IMAGE_DEBUG
    Track track;
#endif
} SearchResult;

void process_image(Image image);
uint8 otsu_calc_threshold(Image image, uint8 min, uint8 max);
void otsu_binarize_image(Image image, uint8 threshould);
SearchResult search(Image image);

extern ElementType element_type;
extern SearchResult search_result;
extern uint8 otsu_threshold;

extern uint8 OTSU_THRESHOLD_MIN;
extern uint8 OTSU_THRESHOLD_MAX;
extern int OSTU_COUNTER_MAX;
extern int OTSU_COMPRESS_RATIO;

#endif /* CODE_IMAGE_H_ */
