#include "image.hpp"
#include <stdlib.h>

Image::Image() {
    this->pixels = (RGB**)malloc(sizeof(RGB*) * kXDim);

    for (int x = 0; x < kXDim; x++) {
        this->pixels[x] = (RGB*)malloc(sizeof(RGB) * kYDim);

        for (int y = 0; y < kYDim; y++) {
            this->pixels[x][y] = kBlack_color;
        }
    }
}

Image::~Image() {
    for (int x = 0; x < kXDim; x++) {
        free(this->pixels[x]);
        this->pixels[x] = nullptr;
    }

    free(this->pixels);
    this->pixels = nullptr;
}

Image::Image(const Image &lvalue) {
    this->pixels = (RGB**)malloc(sizeof(RGB*) * kXDim);

    for (int x = 0; x < kXDim; x++) {
        this->pixels[x] = (RGB*)malloc(sizeof(RGB) * kYDim);

        for (int y = 0; y < kYDim; y++) {
            this->pixels[x][y] = lvalue[x][y];
        }
    }
}

Image Image::operator=(const Image &lvalue) {
    return Image(lvalue);
}