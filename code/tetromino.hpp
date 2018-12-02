#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include "RGB.hpp"
#include <map>
using std::map;

struct Square {
    Square() {}
    Square(unsigned int x, unsigned int y, const RGB &color) {
        reset(x, y, color);
    }
    void reset(unsigned int x, unsigned int y, const RGB &color) {
        this->x = x; this->y = y; this->color = color;
    }
    unsigned int x, y;
    RGB color;
};


class Tetromino {
public:
    Tetromino() {}
    ~Tetromino() {}
    Tetromino(char type);
    bool setSquares(char type);
    void rotate(int times = 0);
    bool moveLeft();
    bool moveRight();
    bool moveDown();
private:
    void init();
    void rotate(char type);
    char type;
    map<char, int (*)[4][2]> all_types_init_coordinates;
    int coordinates[4][2];
    int turn_index;
};

#endif