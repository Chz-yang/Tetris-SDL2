#ifndef BMP_HPP
#define BMP_HPP

#include "bitmap_image.hpp"
#include "RGB.hpp"

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