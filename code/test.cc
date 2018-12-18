#include "bitmap_image.hpp"
#include "RGB.hpp"
#include <iostream>
using namespace std;

int main() {
    bitmap_image pixels;
    pixels.setwidth_height(600, 800);
    for (int x = 0; x < 600; x++) {
        for (int y = 0; y < 800; y++) {
            pixels.set_pixel(x, y, kBlack_color);
        }
    }

    for (int x = 400; x < 405; x++) {
        for (int y = 0; y < 800; y++) {
            pixels.set_pixel(x, y, RGB(245, 222, 179));
        }
    }

    for (int x = 430; x < 575; x++) {
        for (int y = 145; y < 290; y++) {
            pixels.set_pixel(x, y, RGB(240, 255, 255));
        }
    }

    // for (int x = 430; x < 435; x++) {
    //     for (int y = 145; y < 290; y++) {
    //         pixels.set_pixel(x, y, kYellow_color);
    //         pixels.set_pixel(x + 140, y, kYellow_color);
    //     }
    // }

    // for (int y = 145; y < 150; y++) {
    //     for (int x = 430; x < 575; x++) {
    //         pixels.set_pixel(x, y, kYellow_color);
    //         pixels.set_pixel(x, y + 140, kYellow_color);
    //     }
    // }

    pixels.save_image("../resource/img/background.bmp");
}