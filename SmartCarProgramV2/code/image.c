#include "image.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

ElementType element_type = Normal;
SearchResult search_result;

int OSTU_COUNTER_MAX = 10;
int OTSU_THRESHOLD_MIN = 50;
int OTSU_THRESHOLD_MAX = 80;
int OTSU_COMPRESS_RATIO = 1;
int OTSU_THRESHOLD_DELTA = 4;

int otsu_counter = 0;
int otsu_threshold = 0;

void process_image(Image image) {
    if (otsu_counter) {
        otsu_counter --;
    }
    else {
        if (otsu_threshold) otsu_threshold = otsu_calc_threshold(
            image,
            otsu_threshold - OTSU_THRESHOLD_DELTA,
            otsu_threshold + OTSU_THRESHOLD_DELTA // WARNING: Untested
        );
        else otsu_threshold = otsu_calc_threshold(
            image, OTSU_THRESHOLD_MIN, OTSU_THRESHOLD_MAX
        );
        otsu_counter = OSTU_COUNTER_MAX;
    }
    otsu_binarize_image(image, otsu_threshold);
	search_result = search(image);
	element_type = Curve;
}

uint8 otsu_calc_threshold(Image image, uint8 min, uint8 max) {
    int PIXEL_COUNT = HEIGHT * WIDTH / pow(OTSU_COMPRESS_RATIO, 2);
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
        double p1 = (double) c / PIXEL_COUNT;
        if (p1 == 0) continue;
        if (p1 == 1) break;

        double mg = (double) s / PIXEL_COUNT;
        double m = (double) sm / PIXEL_COUNT;
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

const uint8 BOUND_Y_BEGIN = 110;
const uint8 BOUND_COUNT = 10;
const uint8 INVALID_BOUND_COUNT_MAX = 5;
const uint8 BOUND_COUNT_EX = BOUND_COUNT + INVALID_BOUND_COUNT_MAX + 1;
const uint8 BOUND_Y_MIN = BOUND_Y_BEGIN - BOUND_COUNT - INVALID_BOUND_COUNT_MAX;

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

SearchResult search(Image image) {
    uint8 x_lefts[BOUND_COUNT_EX], x_rights[BOUND_COUNT_EX], ys[BOUND_COUNT_EX];
    uint8 x_left = x_lefts[0] = 0, x_right = x_rights[0] = MAX_X;
    uint8 left_invalid_count = 0, right_invalid_count = 0;
    int offset_sum = 0, offset_count = 0, offset_both_begin = 0;
    Track track = Both;
    for (uint8 y = BOUND_Y_BEGIN; offset_count < BOUND_COUNT && y >= BOUND_Y_MIN; y --) {
        if (track != Right) {
            while (x_left < MID_X && image[y][x_left] == EMPTY) x_left ++;
            while (x_left > 0 && image[y][x_left - 1] == ROAD) x_left --;
            if (x_left == MID_X) {
                x_left = x_lefts[offset_count];
                continue;
            }
            if (x_left == 0) {
                left_invalid_count ++;
                if (left_invalid_count > INVALID_BOUND_COUNT_MAX) {
                    if (track == Left) break;
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
            while (x_right < MAX_X && image[y][x_right + 1] == ROAD) x_right ++;
            if (x_right == MID_X) {
                x_right = x_rights[offset_count];
                continue;
            }
            if (x_right == MAX_X) {
                right_invalid_count ++;
                if (right_invalid_count > INVALID_BOUND_COUNT_MAX) {
                    if (track == Right) break;
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

        offset_sum += x_mid - MID_X;
    }

    SearchResult result = { 0 };
    if (offset_count) result.offset = (float) offset_sum / offset_count;
#ifdef IMAGE_DEBUG
    result.track = track;
#endif

    return result;
}

