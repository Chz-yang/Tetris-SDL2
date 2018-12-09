#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include "RGB.hpp"
#include "image.hpp"
#include "window.hpp"
#include <map>
using std::map;

class Tetromino {
  public:
    Tetromino(Window* window, Image &image);
    ~Tetromino() {}
    Tetromino(Window* window, Image &image, char type);
    bool setType(char type);
    void rotate(int times = 0);
    bool move(string direction);
    bool moveLeft();
    bool moveRight();
    bool moveDown();

  private:
    void initAllTypesCoordinates();
    void rotate(char type);
    int getNumOfTypeCoordinates(char type);
    int getTypeCoordinates(char type, int turn_index, int row, int col);
    void flashScreen() const ;
    void mixIntoImage();

  private:
    Image &image;
    Window *window;
    char type;
    RGB color;
    int coordinates[4][2];
    int turn_index;
};

#endif