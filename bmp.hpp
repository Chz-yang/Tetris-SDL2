#ifndef BMP_HPP
#define BMP_HPP

#include "bitmap_image.hpp"
#include <string>

struct RGB {
    RGB(unsigned char red, unsigned char green, unsigned char blue) 
    : red(red), green(green), blue(blue) {}
    unsigned char red, green, blue;
    const bool operator== (const RGB &a) {
        return (red == a.red && green == a.green && blue == a.blue);
    }
    const bool operator!= (const RGB &a) {
        return !(*this == a);
    }
};

const RGB kWhite_color = RGB(255, 255, 255);
const RGB kBlack_color = RGB(0, 0, 0);
const RGB kBlue_color = RGB(0, 0, 255);

class Bitmap {
public:
    Bitmap() {}
    ~Bitmap() {}
    Bitmap(int width, int height);
    bool setHeight(int height);
    bool setWidth(int width);
    unsigned int getHeight() const;
    unsigned int getWidth() const;
    bool convertToBmp(std::string bmp_file_name, RGB **image, int, int);
private:
    void zoomOut(int, int, int, int, const RGB &color);
    void setFrame(RGB **, int, int, int, int, const RGB &color);
    void addFrame(int, int, int, int, const RGB &color);
    bitmap_image image;
};

#endif