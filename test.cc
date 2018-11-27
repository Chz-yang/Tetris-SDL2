#include "bmp.hpp"
#include <iostream>
using namespace std;

int main() {
    Bitmap bmp(400, 800);
    RGB **image = (RGB **)malloc(sizeof(RGB*) * 20);
    for (int i = 0; i < 20; i++) {
        image[i] = (RGB *)malloc(sizeof(RGB) * 10);
        for (int j = 0; j < 10; j++) {
            image[i][j] = kBlack_color;
        }
    }
    image[0][5] = kBlue_color;
    image[1][5] = kBlue_color;
    image[2][5] = kBlue_color;
    image[3][5] = kBlue_color;

    bmp.convertToBmp("resource/img/test.bmp", image, 10, 20);
    for (int i = 0; i < 20; i++) {
        free(image[i]);
    }
    free(image);
}