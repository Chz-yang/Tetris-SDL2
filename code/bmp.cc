#include "bmp.hpp"
#include <iostream>
using namespace std;

Bitmap::Bitmap(int width, int height) {
    /* init bitmap with width and height using positive numbers */
    setWidth(width);
    setHeight(height);
}

bool Bitmap::setHeight(int height) {
    /* set bitmap height with a positive number */
    if (height <= 0) {return false;}

    this->image.setwidth_height(getWidth(), height);
    return true;
}

bool Bitmap::setWidth(int width) {
    /* set bitmap width with a positive number */
    if (width <= 0) {return false;}

    this->image.setwidth_height(width, getHeight());
    return true;
}

unsigned int Bitmap::getHeight() const {
    /* get height of bitmap */
    return this->image.height();
}

unsigned int Bitmap::getWidth() const {
    /* get width of bitmap */
    return this->image.width();
}

bool Bitmap::convertToBmp(std::string bmp_file_name, RGB **image, 
                            int image_width, int image_height) {
    /* convert a image array filed with 24-bits pixel to bitmap */
    int width_scale =  getWidth() / image_width;
    int height_scale = getHeight() / image_height;
    this->image.setwidth_height(getWidth() + 0.05 * width_scale, 
                                getHeight() + 0.05 * height_scale);

    for (int x = 0; x < image_width; x++) {
        for (int y = 0; y < image_height; y++) {
            zoomOut(x, y, width_scale, height_scale, image[x][y]);
        }
    }
    setFrame(image, image_width, image_height, 
             width_scale, height_scale, kWhite_color);
    this->image.save_image(bmp_file_name);
}

void Bitmap::zoomOut(int x, int y, int width_scale, int height_scale,
                     const RGB &color) {
    for (int i = x * width_scale; i < (x + 1) * width_scale; i++) {
        for (int j = y * height_scale; j < (y + 1) * height_scale; j++) {
            this->image.set_pixel(i, j, color);
        }
    }
}

void Bitmap::setFrame(RGB **image, int image_width, int image_height, 
                      int width_scale, int height_scale, const RGB &color) {
    for (int x = 0; x < image_width; x++) {
        for (int y = 0; y < image_height; y++) {
            if (image[x][y] != kBlack_color) {
                addFrame(x, y, width_scale, height_scale, color);
            }
        }
    }
}

void Bitmap::addFrame(int x, int y, int width_scale, int height_scale, 
                      const RGB &color) {
    for (int i = x * width_scale; i < (x + 1.05) * width_scale; i++) {
        for (int j = y * height_scale; j < (y + 0.05) * height_scale; j++) {
            this->image.set_pixel(i, j, color);
            this->image.set_pixel(i, j + height_scale, color);
        }
    }

    for (int i = x * width_scale; i < (x + 0.05) * width_scale; i++) {
        for (int j = y * height_scale; j < (y + 1.05) * height_scale; j++) {
            this->image.set_pixel(i, j, color);
            this->image.set_pixel(i + width_scale, j, color);
        }
    }
}