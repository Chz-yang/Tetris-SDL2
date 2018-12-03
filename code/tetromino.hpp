#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include "RGB.hpp"
#include <map>
using std::map;

class Tetromino {
public:
    Tetromino();
    ~Tetromino() {}
    Tetromino(char type);
    bool setSquares(char type);
    void rotate(int times = 0);
    bool moveLeft();
    bool moveRight();
    bool moveDown();
private:
    void initAllTypesCoordinates();
    void rotate(char type);
    map<char, int (*)[4][2]> all_types_init_coordinates;
    char type;
    RGB color;
    int coordinates[4][2];
    int turn_index;
};

#endif