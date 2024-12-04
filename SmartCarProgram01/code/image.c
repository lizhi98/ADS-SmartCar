#include "image.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

ElementType element_type = Normal;
double angle = 0;

void process_image(Image image) {
    binarize_image_otsu(image);
	angle = search_bound(image);
	element_type = fabs(angle) < 10. ? Normal : Curve;
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

// #define SEARCH_J_STEP 6
// #define SEARCH_J_START (HEIGHT - 1)
// #define SEARCH_J_POINT_NUM 6
// #define SEARCH_J_SEG_NUM 5 // 6 - 1
// #define MID_J 93 // 186 / 2
// double search_bound(Image image) {
//     uint8 left_js[SEARCH_J_POINT_NUM];
//     uint8 right_js[SEARCH_J_POINT_NUM];
//     uint8 left_j_deltas[SEARCH_J_SEG_NUM];
//     uint8 right_j_deltas[SEARCH_J_SEG_NUM];
//     for (uint8 n = 0, i = SEARCH_J_START; n < SEARCH_J_POINT_NUM; n ++, i -= SEARCH_J_STEP) {
//         int new_left_j, new_right_j;
//         for (new_left_j = 0; new_left_j < MID_J; new_left_j ++) {
//             if (image[i][new_left_j]) break;
//         }
//         for (new_right_j = MAX_J; new_right_j > MID_J; new_right_j --) {
//             if (image[i][new_right_j]) break;
//         }
//         if (n) {
//             left_j_deltas[n - 1] = new_left_j - left_j;
//             right_j_deltas[n - 1] = new_right_j - right_j;
//         }
//     }
// }

double search_bound(Image image) {
    uint8 i_start = HEIGHT - 10;
	uint8 i_end = HEIGHT / 3;
	uint8 mid_j = WIDTH / 2;
	uint8 left_j = 0, right_j = MAX_J;
	uint8 left_valid_count = 0, right_valid_count = 0;
	bool left_valid = false, right_valid = false;
    bool left_blind = false, right_blind = false;
	uint8 secant_start_set = false;
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
                if (j && left_j - j < 5) {
			        left_j = j;
                    image[i][j] = LEFT_BOUND;
                }
                else if (! left_blind) {
                    if (left_i_start - i < 10) {
                        left_valid = false;
                    }
                    else {
                        left_blind = true;
                        left_i_end = i + 1;
                        left_j_end = left_j;
                        left_m = (double) (left_j_end - left_j_start) / (double) (left_i_end - left_i_start);
                        image[i][j] = INVALID_LINE;
                    }
                }
            }
            if (left_blind) {
                uint8 left_j_attempt = left_j_end + (i - left_i_end) * left_m;
                bool bound_found = false;
                if (left_j_attempt < 0 || left_j_attempt > MAX_J) break;
                if (image[i][left_j_attempt]) {
                    for (uint8 dj = 0; dj < 3; dj ++) {
                        uint8 j = left_j_attempt - dj;
                        if (j < 0) break;
                        if (! image[i][j]) {
                            left_j = j + 1;
                            image[i][left_j] = LEFT_BOUND;
                            bound_found = true;
                            break;
                        }
                    }
                }
                else {
                    for (uint8 dj = 0; dj < 3; dj ++) {
                        uint8 j = left_j_attempt + dj;
                        if (image[i][j]) {
                            left_j = j;
                            image[i][left_j] = LEFT_BOUND;
                            bound_found = true;
                            break;
                        }
                    }
                }
                if (! bound_found) {
                    left_j = left_j_attempt;
                    image[i][left_j] = LEFT_BOUND_ATTEMPT;
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
                if (MAX_J - j && right_j - j > - 5) {
			        right_j = j;
                    image[i][j] = RIGHT_BOUND;
                }
                else if (! right_blind) {
                    if (left_i_start - i < 10) {
                        left_valid = false;
                    }
                    else {
                        right_blind = true;
                        right_i_end = i + 1;
                        right_j_end = right_j;
                        right_m = (double) (right_j_end - right_j_start) / (double) (right_i_end - right_i_start);
                        image[i][j] = INVALID_LINE;
                    }
                }
            }
            if (right_blind) {
                uint8 right_j_attempt = right_j_end + (i - right_i_end) * right_m;
                if (right_j_attempt < 0 || right_j_attempt > MAX_J) break;
                bool bound_found = false;
                if (image[i][right_j_attempt]) {
                    for (uint8 dj = 0; dj < 3; dj ++) {
                        uint8 j = right_j_attempt + dj;
                        if (j > MAX_J) break;
                        if (! image[i][j]) {
                            right_j = j - 1;
                            image[i][right_j] = RIGHT_BOUND;
                            bound_found = true;
                            break;
                        }
                    }
                }
                else {
                    for (uint8 dj = 0; dj < 3; dj ++) {
                        uint8 j = right_j_attempt - dj;
                        if (image[i][j]) {
                            right_j = j;
                            image[i][right_j] = RIGHT_BOUND;
                            bound_found = true;
                            break;
                        }
                    }
                }
                if (! bound_found) {
                    right_j = right_j_attempt;
                    image[i][right_j] = RIGHT_BOUND_ATTEMPT;
                }
            }
			break;
		}
		if (left_valid && right_valid) {
		    if (! left_blind && ! right_blind) for (uint8 j = left_j + 1; j < right_j - 1; j ++) image[i][j] = ROAD;
			uint8 j_mid = (left_j + right_j) / 2;
			if (! secant_start_set && i < SEC_I_START) {
				secant_start_set = true;
				mid_i_start = i;
				mid_j_start = j_mid;
				image[i][j_mid] = TERMINAL;
			}
			else if (i == mid_i_start - SEC_I_DELTA) {
				mid_i_end = i;
				mid_j_end = j_mid;
				image[i][j_mid] = TERMINAL;
			}
			else {
				image[i][j_mid] = MID_LINE;
			}
		}
	}

    if (! left_valid || ! right_valid) return 0;

	uint8 dj = mid_j_end - mid_j_start;
	double phi = dj ? atan((double) SEC_I_DELTA / (double) dj) / PI * 180 : 90;
    double angle = (phi < 0 ? - 90 : 90) - phi;

	return angle;
}

