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

    for (int row = 0; row < image_height; row++) {
        for (int col = 0; col < image_width; col++) {
            zoomOut(col, row, width_scale, height_scale, image[row][col]);
        }
    }
    setFrame(image, image_width, image_height, 
             width_scale, height_scale, kWhite_color);
    this->image.save_image(bmp_file_name);
}

void Bitmap::zoomOut(int col, int row, int width_scale, int height_scale,
                     const RGB &color) {
    for (int y= row * height_scale; y < (row + 1) * height_scale; y++) {
        for (int x = col * width_scale; x < (col + 1) * width_scale; x++) {
            this->image.set_pixel(x, y, color);
        }
    }
}

void Bitmap::setFrame(RGB **image, int image_width, int image_height, 
                      int width_scale, int height_scale, const RGB &color) {
    for (int row = 0; row < image_height; row++) {
        for (int col = 0; col < image_width; col++) {
            if (image[row][col] != kBlack_color) {
                addFrame(col, row, width_scale, height_scale, color);
            }
        }
    }
}

void Bitmap::addFrame(int col, int row, int width_scale, int height_scale, 
                      const RGB &color) {
    for (int y = row * height_scale; y < (row + 0.05) * height_scale; y++) {
        for (int x = col * width_scale; x < (col + 1.05) * width_scale; x++) {
            this->image.set_pixel(x, y, color);
            this->image.set_pixel(x, y + height_scale, color);
        }
    }

    for (int y = row * height_scale; y < (row + 1.05) * height_scale; y++) {
        for (int x = col * width_scale; x < (col + 0.05) * width_scale; x++) {
            this->image.set_pixel(x, y, color);
            this->image.set_pixel(x + width_scale, y, color);
        }
    }
}