#include "image.h"
#include <zf_device_mt9v03x.h>
#include <math.h>

void init_image_sending() {

}

ElementType element_type = Normal;

int HEIGHT = 120;
int WIDTH = 188;
int PIXELS = 120 * 188;


ImageResult process_image(Image image) {
    ImageResult result;

    result.midline_delta = 0;
    result.element_type = Normal;

    return result;
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
        printf("var = %lf, k = %d\n", var, k);
        if (var > var_max) {
            var_max = var;
            k_best = k;
        }
    }
    
    printf("k_best = %d\n", k_best);

    for (int i = 0; i < HEIGHT; i ++) {
        for (int j = 0; j < WIDTH; j ++) {
            image[i][j] = image[i][j] > k_best;
        }
    }
    return;
}

const int EMPTY = 0;
const int ROAD = 1;
const int LEFT_BOUND = 2;
const int RIGHT_BOUND = 3;
const int MID_LINE = 4;

void search_bound(Image image) {
	int target_i = HEIGHT / 2;
	int mid_j = WIDTH / 2;
	int left_j = 0, right_j = WIDTH - 1;
	for (int i = HEIGHT - 1; i >= target_i; i --) {
		for (int j = left_j; j < mid_j; j ++) if (image[i][j]) {
			image[i][j] = LEFT_BOUND;
			left_j = j;
			break;
		}
		for (int j = right_j; j > mid_j; j --) if (image[i][j]) {
			image[i][j] = RIGHT_BOUND;
			right_j = j;
			break;
		}
		for (int j = left_j + 1; j < right_j - 1; j ++) image[i][j] = ROAD;
		image[i][(left_j + right_j) / 2] = MID_LINE;
	}
}
/*
int main() {
    binarize_image_otsu(image);
	search_bound(image);

    for (int i = 0; i < HEIGHT; i ++) {
        for (int j = 0; j < WIDTH; j ++) {
            printf("%c", image[i][j] == 1 ? ' ' : image[i][j] + '0');
        }
        printf("\n");
    }

    return 0;
}
*/
