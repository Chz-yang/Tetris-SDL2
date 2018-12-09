#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "RGB.hpp"
#include <iostream>

const int kXDim = 10, kYDim = 20;

class Image {
  public:
    Image();
    ~Image();
    Image(const Image &); // deep copy
    Image operator=(const Image &);
    RGB** getPixels() {return pixels;}
    RGB** getPixels() const {return pixels;}
    RGB* operator[](int x) {return pixels[x];}
    RGB* operator[](int x) const {return pixels[x];}

  private:
    RGB** pixels;
};

#endif