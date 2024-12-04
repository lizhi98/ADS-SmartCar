#include "image.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

ElementType element_type = Normal;
double angle = 0;

void process_image(Image image) {
    binarize_image_otsu(image);
	angle = search_bound(image);
	element_type = fabs(angle) < 0.5 ? Normal : Curve;
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

const uint8 SEC_I_START = 5;
const uint8 SEC_I_DELTA = 30;

double search_bound(Image image) {
	int target_i = HEIGHT / 2;
	int mid_j = WIDTH / 2;
	int left_j = 0, right_j = WIDTH - 1;
	int left_valid = false, right_valid = false;
	int secant_start_set = false;
	int i_start, j_start, i_end, j_end;
	for (int i = HEIGHT - 1; i >= target_i; i --) {
		for (int j = 0; j < mid_j; j ++) if (image[i][j]) {
			if (! left_valid && j) left_valid = true;
			if (left_valid) image[i][j] = LEFT_BOUND;
			left_j = j;
			break;
		}
		for (int j = WIDTH - 1; j > mid_j; j --) if (image[i][j]) {
			if (! right_valid && WIDTH - 1 - j) right_valid = true;
			if (right_valid) image[i][j] = RIGHT_BOUND;
			right_j = j;
			break;
		}
		for (int j = left_j + 1; j < right_j - 1; j ++) image[i][j] = ROAD;
		if (left_valid && right_valid) {
			int j_mid = (left_j + right_j) / 2;
			if (! secant_start_set && HEIGHT - 1 - i >= SEC_I_START) {
				secant_start_set = true;
				i_start = i;
				j_start = j_mid;
				image[i][j_mid] = TERMINAL;
			}
			else if (i == i_start - SEC_I_DELTA) {
				i_end = i;
				j_end = j_mid;
				image[i][j_mid] = TERMINAL;
			}
			else {
				image[i][j_mid] = MID_LINE;
			}
		}
	}

	int dj = j_end - j_start;
	double phi = dj ? atan((double) SEC_I_DELTA / (double) dj) / M_PI * 180 : 90;
    double angle = (phi < 0 ? - 90 : 90) - phi;

	return angle;
}

