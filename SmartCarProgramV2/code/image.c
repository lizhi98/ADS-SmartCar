#include "image.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

ElementType element_type = Normal;
SearchResult search_result;

int OSTU_COUNTER_MAX = 10;
uint8 OTSU_THRESHOLD_MIN = 50;
uint8 OTSU_THRESHOLD_MAX = 80;
int OTSU_COMPRESS_RATIO = 2;
int OTSU_COMPRESS_RATIO_SQUARE = 4; // OTSU_COMPRESS_RATIO * OTSU_COMPRESS_RATIO;
int OTSU_THRESHOLD_DELTA = 4;

uint8 otsu_counter = 0;
uint8 otsu_threshold = 0;

uint8 image_buffer[HEIGHT][REAL_WIDTH] = { 0 };

void process_image(Image image) {
    memcpy(image_buffer, image, sizeof (uint8) * REAL_WIDTH * HEIGHT);
    if (otsu_counter) {
        otsu_counter --;
    }
    else {
        if (otsu_threshold) otsu_threshold = otsu_calc_threshold(
            image_buffer,
            otsu_threshold - OTSU_THRESHOLD_DELTA,
            otsu_threshold + OTSU_THRESHOLD_DELTA // WARNING: Untested
        );
        else otsu_threshold = otsu_calc_threshold(
            image_buffer, OTSU_THRESHOLD_MIN, OTSU_THRESHOLD_MAX
        );
        otsu_counter = OSTU_COUNTER_MAX;
    }
    otsu_binarize_image(image_buffer, otsu_threshold);
	search_result = search(image_buffer);
	element_type = Curve; // TODO
}

uint8 otsu_calc_threshold(Image image, uint8 min, uint8 max) {
    int OTSU_PIXEL_COUNT = HEIGHT * WIDTH / OTSU_COMPRESS_RATIO_SQUARE;
    double var_max = 0;
    uint8 k_best;
    for (uint8 k = min; k <= max; k ++) {
        int c = 0, s = 0, sm = 0;
        for (int i = 0; i < HEIGHT; i += OTSU_COMPRESS_RATIO) {
            for (int j = 0; j < WIDTH; j += OTSU_COMPRESS_RATIO) {
                if (image[i][j] <= k) {
                    c ++;
                    sm += image[i][j];
                }
                s += image[i][j];
            }
        }
        double p1 = (double) c / OTSU_PIXEL_COUNT;
        if (p1 == 0) continue;
        if (p1 == 1) break;

        double mg = (double) s / OTSU_PIXEL_COUNT;
        double m = (double) sm / OTSU_PIXEL_COUNT;
        double var = pow(mg * p1 - m, 2) / (p1 * (1 - p1));
        if (var > var_max) {
            var_max = var;
            k_best = k;
        }
    }
    return k_best;
}

void otsu_binarize_image(Image image, uint8 threshould) {
    for (uint8 i = 0; i < HEIGHT; i ++)
        for (uint8 j = 0; j < WIDTH; j ++)
            image[i][j] = image[i][j] > threshould;
}

const uint8 EMPTY = 0;
const uint8 ROAD = 1;
const uint8 BOUND = 2;
const uint8 MID_LINE = 3;

#define BOUND_Y_BEGIN 110
#define BOUND_COUNT 10
#define INVALID_BOUND_COUNT_MAX 5
#define BOUND_COUNT_EX 16 // BOUND_COUNT + INVALID_BOUND_COUNT_MAX + 1
#define BOUND_Y_MIN 95 // BOUND_Y_BEGIN - BOUND_COUNT - INVALID_BOUND_COUNT_MAX
#define BOUND_X_BACK_MAX 4

const float OFFSET_MIN = 1.0;

const uint8 STD_ROAD_HALF_WIDTHS[] = {
    83,     82,     81,     80,
    79,     78,     78,     77,
    76,     75,     74,     73,
    72,     71,     70,     69,
    69,     68,     67,     66,
    65,     64,     63,     62,
    61,     61,     60,     59,
    58,     57,     56,     55,
    54,     54,     53,     52,
    51,     50,     49,     48,
    47,     46,     45,     45,
    43,     42,     41,     40,
    39,     38,     37,     36,
    35,     34,     33,     32,
    31,     30,     29,     28,
    27,     26,     25,     24,
    23,     22,     21,     20,
};

float get_offset_weight(uint8 y) {
    return 1.0 - (BOUND_Y_BEGIN - y) * 0.2;
}

SearchResult search(Image image) {
    uint8 x_lefts[BOUND_COUNT_EX], x_rights[BOUND_COUNT_EX], ys[BOUND_COUNT_EX];
    uint8 x_left = x_lefts[0] = 0, x_right = x_rights[0] = MAX_X;
    uint8 left_invalid_count = 0, right_invalid_count = 0;
    float offset_sum = 0, offset_weight_sum = 0;
    uint8 offset_count = 0, offset_both_begin = 0;
    Track track = Both;

    for (uint8 y = BOUND_Y_BEGIN; offset_count < BOUND_COUNT && y >= BOUND_Y_MIN; y --) {
        if (track != Right) {
            while (x_left < MID_X && image[y][x_left] == EMPTY) x_left ++;
            uint8 x_left_max = x_left > BOUND_X_BACK_MAX ? x_left - BOUND_X_BACK_MAX : 0;
            while (x_left > x_left_max && image[y][x_left - 1] == ROAD) x_left --;
            if (x_left == MID_X) {
                x_left = x_lefts[offset_count];
                continue;
            }
            if (x_left == x_left_max) {
                left_invalid_count ++;
                if (left_invalid_count > INVALID_BOUND_COUNT_MAX) {
                    if (track == Left) {
                        track = None;
                        break;
                    }
                    track = Right;
                }
            }
#ifdef IMAGE_DEBUG
            else image[y][x_left] = BOUND;
#endif
            x_lefts[offset_count + 1] = x_left;
        }

        if (track != Left) {
            while (x_right > MID_X && image[y][x_right] == EMPTY) x_right --;
            uint8 x_right_max = x_right + BOUND_X_BACK_MAX < MAX_X ? x_right + BOUND_X_BACK_MAX : MAX_X;
            while (x_right < x_right_max && image[y][x_right + 1] == ROAD) x_right ++;
            if (x_right == MID_X) {
                x_right = x_rights[offset_count];
                continue;
            }
            if (x_right == x_right_max) {
                right_invalid_count ++;
                if (right_invalid_count > INVALID_BOUND_COUNT_MAX) {
                    if (track == Right) {
                        track = None;
                        break;
                    }
                    track = Left;
                }
            }
#ifdef IMAGE_DEBUG
            else image[y][x_right] = BOUND;
#endif
            x_rights[offset_count + 1] = x_right;
        }

        if (! offset_both_begin) offset_both_begin = offset_count + 1;

        ys[offset_count + 1] = y;

        offset_count ++;
    }

    SearchResult result = { 0 };

#ifdef IMAGE_DEBUG
    result.track = track;
#endif

    if (track != None) {
        for (uint8 i = 1, x_mid; i <= offset_count; i ++) {
            if (track == Both) x_mid = (x_lefts[i] + x_rights[i]) >> 1;
            else {
                uint8 road_i = MAX_Y - ys[i];
                if (track == Left) x_mid = x_lefts[i] + STD_ROAD_HALF_WIDTHS[road_i];
                else x_mid = x_rights[i] - STD_ROAD_HALF_WIDTHS[road_i];
            }
#ifdef IMAGE_DEBUG
            image[ys[i]][x_mid] = MID_LINE;
#endif
            float w = get_offset_weight(i);
            offset_sum += (x_mid - MID_X) * w;
            offset_weight_sum += w;
        }

        if (offset_count) {
            result.offset = offset_sum / offset_weight_sum;
            if (abs(result.offset) < OFFSET_MIN) result.offset = 0;
        }
    }

    return result;
}

