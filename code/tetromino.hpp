#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include "RGB.hpp"
#include "image.hpp"
#include "window.hpp"
#include <map>
using std::map;

class Tetromino {
  public:
    Tetromino(Window* window, Image *image);
    ~Tetromino() {}
    Tetromino(Window* window, Image *image, char type);
    bool newTetromino();
    int move(string key);

  private:
    int rotate();
    int moveLeft();
    int moveRight();
    int moveDown();
    int getNumOfTypeCoordinates(char type);
    int getTypeCoordinates(char type, int turn_index, int row, int col);
    void flashScreen(Image *image);
    int isValid(int x, int y);
    bool setType(char type);

  private:
    Image *image;
    Window *window;
    char type;
    RGB color;
    int coordinates[4][2];
    int turn_index;
};

#endif