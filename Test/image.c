#include "../SmartCarProgram01/code/image.h"
#include "./Data/curve_1.c"
#include <stdio.h>
#include <math.h>

const int COLORS[] = { '0', '7', '2', '2', '1', '3', '5', '6', '6' };

int main() {
    binarize_image_otsu(image);
	double k = search_bound(image);

    for (int i = 0; i < HEIGHT; i ++) {
        for (int j = 0; j < WIDTH; j ++) {
            printf("\x1B[4%cm%c\x1B[0m", COLORS[image[i][j]], image[i][j] + '0');
        }
        printf("\n");
    }
	printf("[angle = %lf°]\n", k);

    return 0;
}
