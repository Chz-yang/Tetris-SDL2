#ifndef RGB_HPP
#define RGB_HPP

struct RGB {
    RGB() {}
    RGB(unsigned char red, unsigned char green, unsigned char blue) 
    : red(red), green(green), blue(blue) {}
    unsigned char red, green, blue;
    const bool operator== (const RGB &a) const {
        return (red == a.red && green == a.green && blue == a.blue);
    }
    const bool operator!= (const RGB &a) const {
        return !(*this == a);
    }
};

const RGB kWhite_color = RGB(255, 255, 255);
const RGB kBlack_color = RGB(0, 0, 0);
const RGB kBlue_color = RGB(0, 0, 255);

#endif