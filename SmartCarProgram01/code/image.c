#include "image.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

ElementType element_type = Normal;
double angle = 0;

void process_image(Image image) {
    binarize_image_otsu(image);
	angle = search_bound(image);
	element_type = fabs(angle) < 10 ? Normal : Curve;
}

void binarize_image_otsu(Image image) {
    double var_max = 0;
    int k_best;
    for (int k = 0; k < 255; k ++) {
        int c = 0, s = 0, sm = 0;
        for (int i = 0; i < HEIGHT; i ++) {
            for (int j = 0; j < WIDTH; j ++) {
                if (image[i][j] <= k) {
                    c ++;
                    sm += image[i][j];
                }
                s += image[i][j];
            }
        }
        double p1 = (double) c / PIXELS;
        if (p1 == 0) continue;
        if (p1 == 1) break;

        double mg = (double) s / PIXELS;
        double m = (double) sm / PIXELS;
        double var = pow(mg * p1 - m, 2) / (p1 * (1 - p1));
        if (var > var_max) {
            var_max = var;
            k_best = k;
        }
    }

    for (int i = 0; i < HEIGHT; i ++) {
        for (int j = 0; j < WIDTH; j ++) {
            image[i][j] = image[i][j] > k_best;
        }
    }

    return;
}

const uint8 EMPTY = 0;
const uint8 ROAD = 1;
const uint8 LEFT_BOUND = 2;
const uint8 RIGHT_BOUND = 3;
const uint8 INVALID_LINE = 4;
const uint8 MID_LINE = 5;
const uint8 TERMINAL = 6;
const uint8 LEFT_BOUND_ATTEMPT = 7;
const uint8 RIGHT_BOUND_ATTEMPT = 8;

const uint8 SEC_I_START = HEIGHT - 6;
const uint8 SEC_I_DELTA = 30;

#ifdef IMAGE_DEBUG
const bool digits[10][15] = {
    {
        1, 1, 1,
        1, 0, 1,
        1, 0, 1,
        1, 0, 1,
        1, 1, 1
    },
    {
        0, 0, 1,
        0, 0, 1,
        0, 0, 1,
        0, 0, 1,
        0, 0, 1
    },
    {
        1, 1, 1,
        0, 0, 1,
        1, 1, 1,
        1, 0, 0,
        1, 1, 1
    },
    {
        1, 1, 1,
        0, 0, 1,
        1, 1, 1,
        0, 0, 1,
        1, 1, 1
    },
    {
        1, 0, 1,
        1, 0, 1,
        1, 1, 1,
        0, 0, 1,
        0, 0, 1
    },
    {
        1, 1, 1,
        1, 0, 0,
        1, 1, 1,
        0, 0, 1,
        1, 1, 1
    },
    {
        1, 1, 1,
        1, 0, 0,
        1, 1, 1,
        1, 0, 1,
        1, 1, 1
    },
    {
        1, 1, 1,
        0, 0, 1,
        0, 0, 1,
        0, 0, 1,
        0, 0, 1
    },
    {
        1, 1, 1,
        1, 0, 1,
        1, 1, 1,
        1, 0, 1,
        1, 1, 1
    },
    {
        1, 1, 1,
        1, 0, 1,
        1, 1, 1,
        0, 0, 1,
        1, 1, 1
    }
};
#endif

double search_bound(Image image) {
    uint8 i_start = HEIGHT - 4;
	uint8 i_end = HEIGHT / 3;
	uint8 mid_j = WIDTH / 2;
	uint8 left_j = 0, right_j = MAX_J;
	uint8 left_valid_count = 0, right_valid_count = 0;
	bool left_valid = false, right_valid = false;
    bool left_blind = false, right_blind = false;
	bool secant_start_set = false;
	uint8 mid_i_start, mid_j_start, mid_i_end, mid_j_end;
	uint8 left_i_start, left_j_start, left_i_end, left_j_end;
	uint8 right_i_start, right_j_start, right_i_end, right_j_end;
    double left_m, right_m;

	for (uint8 i = i_start; i >= i_end; i --) {
		for (uint8 j = 0; j < mid_j; j ++) if (image[i][j]) {
			if (! left_valid) {
                if (j) {
                    if (++ left_valid_count == 5) {
                        left_valid = true;
                        left_i_start = i;
                        left_j_start = j;
                    }
                }
                else left_valid_count = 0;
            }
			if (left_valid) {
                if (j && left_j - j < 5 && (left_j == 0 || left_j - j > - 5)) {
			        left_j = j;
#ifdef IMAGE_DEBUG
                    image[i][j] = LEFT_BOUND;
#endif
                }
                else if (! left_blind) {
                    if (left_i_start - i < 7) {
                        left_valid = false;
                        left_valid_count = 0;
                    }
                    else {
                        left_blind = true;
                        left_i_end = i + 1;
                        left_j_end = left_j;
                        left_m = (double) (left_j_end - left_j_start) / (double) (left_i_end - left_i_start);
#ifdef IMAGE_DEBUG
                        image[i][j] = INVALID_LINE;
#endif
                    }
                }
            }
            if (left_blind) {
                sint8 left_j_attempt = left_j_end + (i - left_i_end) * left_m;
                bool bound_found = false;
                if (left_j_attempt < 0 || left_j_attempt > MAX_J) break;
                if (image[i][left_j_attempt]) {
                    for (uint8 dj = 0; dj < 3; dj ++) {
                        sint8 j = left_j_attempt - dj;
                        if (j < 0) break;
                        if (! image[i][j]) {
                            left_j = j + 1;
#ifdef IMAGE_DEBUG
                            image[i][left_j] = LEFT_BOUND;
#endif
                            bound_found = true;
                            break;
                        }
                    }
                }
                else {
                    for (uint8 dj = 0; dj < 3; dj ++) {
                        sint8 j = left_j_attempt + dj;
                        if (image[i][j]) {
                            left_j = j;
#ifdef IMAGE_DEBUG
                            image[i][left_j] = LEFT_BOUND;
#endif
                            bound_found = true;
                            break;
                        }
                    }
                }
                if (! bound_found) {
                    left_j = left_j_attempt;
#ifdef IMAGE_DEBUG
                    image[i][left_j] = LEFT_BOUND_ATTEMPT;
#endif
                }
            }
			break;
		}
		for (uint8 j = MAX_J; j > mid_j; j --) if (image[i][j]) {
			if (! right_valid) {
                if (MAX_J - j) {
                    if (++ right_valid_count == 5) {
                        right_valid = true;
                        right_i_start = i;
                        right_j_start = j;
                    }
                }
                else right_valid_count = 0;
            }
			if (right_valid) {
                if (MAX_J - j && right_j - j > - 5 && (right_j == MAX_J || right_j - j < 5)) {
			        right_j = j;
#ifdef IMAGE_DEBUG
                    image[i][j] = RIGHT_BOUND;
#endif
                }
                else if (! right_blind) {
                    if (right_i_start - i < 7) {
                        right_valid = false;
                        right_valid_count = 0;
                    }
                    else {
                        right_blind = true;
                        right_i_end = i + 1;
                        right_j_end = right_j;
                        right_m = (double) (right_j_end - right_j_start) / (double) (right_i_end - right_i_start);
                        if (i == 90) printf("OK\n");
#ifdef IMAGE_DEBUG
                        image[i][j] = INVALID_LINE;
#endif
                    }
                }
            }
            if (right_blind) {
                sint8 right_j_attempt = right_j_end + (i - right_i_end) * right_m;
                if (right_j_attempt < 0 || right_j_attempt > MAX_J) break;
                bool bound_found = false;
                if (image[i][right_j_attempt]) {
                    for (uint8 dj = 0; dj < 3; dj ++) {
                        sint8 j = right_j_attempt + dj;
                        if (j > MAX_J) break;
                        if (! image[i][j]) {
                            right_j = j - 1;
#ifdef IMAGE_DEBUG
                            image[i][right_j] = RIGHT_BOUND;
#endif
                            bound_found = true;
                            break;
                        }
                    }
                }
                else {
                    for (uint8 dj = 0; dj < 3; dj ++) {
                        sint8 j = right_j_attempt - dj;
                        if (image[i][j]) {
                            right_j = j;
#ifdef IMAGE_DEBUG
                            image[i][right_j] = RIGHT_BOUND;
#endif
                            bound_found = true;
                            break;
                        }
                    }
                }
                if (! bound_found) {
                    right_j = right_j_attempt;
#ifdef IMAGE_DEBUG
                    image[i][right_j] = RIGHT_BOUND_ATTEMPT;
#endif
                }
            }
			break;
		}
		if (left_valid && right_valid) {
#ifdef IMAGE_DEBUG
		    if (! left_blind && ! right_blind) for (uint8 j = left_j + 1; j < right_j - 1; j ++) image[i][j] = ROAD;
#endif
			uint8 j_mid = (left_j + right_j) / 2;
			if (! secant_start_set && i < SEC_I_START) {
				secant_start_set = true;
				mid_i_start = i;
				mid_j_start = j_mid;
#ifdef IMAGE_DEBUG
				image[i][j_mid] = TERMINAL;
#endif
			}
			else if (i == mid_i_start - SEC_I_DELTA) {
				mid_i_end = i;
				mid_j_end = j_mid;
#ifdef IMAGE_DEBUG
				image[i][j_mid] = TERMINAL;
#endif
                break;
			}
#ifdef IMAGE_DEBUG
			else {
				image[i][j_mid] = MID_LINE;
			}
#endif
		}
	}

    double angle;

    if (! left_valid || ! right_valid) {
        angle = 0;
    }
    else {
        sint8 dj = mid_j_end - mid_j_start;
        double phi = dj ? atan((double) SEC_I_DELTA / (double) dj) / PI * 180 : 90;
        angle = (phi < 0 ? - 90 : 90) - phi;
    }

#ifdef IMAGE_DEBUG
    for (int i = 0; i < 3; i ++) {
        for (int j = 0; j < 5; j ++) {
            image[j + 5][i + 5] = digits[(int) angle / 10][j * 3 + i] * 5;
        }
    }
    for (int i = 0; i < 3; i ++) {
        for (int j = 0; j < 5; j ++) {
            image[j + 5][i + 10] = digits[(int) angle % 10][j * 3 + i] * 5;
        }
    }
#endif

	return angle;
}

