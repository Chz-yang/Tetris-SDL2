#include "tetromino.hpp"
#include <string>
#include <vector>
#include <stdint.h>
#include <algorithm>
#include <iostream>
using std::make_pair;
using std::vector;

const int S[][4][2] = {
    {{4, 0}, {4, 0}, {5, -1}, {6, -1}},
    {{4, -1}, {4, -2}, {5, 0}, {5, -1}},
};

const int Z[][4][2] = {
    {{4, -1}, {5, 0}, {5, -1}, {6, 0}},
    {{4, 0}, {4, -1}, {5, -1}, {5, -2}},
};

const int L[][4][2] = {
    {{4, 0}, {4, -1}, {4, -2}, {5, 0}},
    {{4, 0}, {4, -1}, {5, -1}, {6, -1}},
    {{4, -2}, {5, 0}, {5, -1}, {5, -2}},
    {{4, 0}, {5, 0}, {6, 0}, {6, -1}},
};

const int J[][4][2] = {
    {{4, 0}, {5, 0}, {5, -1}, {5, -2}},
    {{4, 0}, {4, -1}, {5, 0}, {6, 0}},
    {{4, 0}, {4, -1}, {4, -2}, {5, -2}},
    {{4, -1}, {5, -1}, {6, 0}, {6, -1}},
};

const int I[][4][2] = {
    {{4, 0}, {4, -1}, {4, -2}, {4, -3}},
    {{3, 0}, {4, 0}, {5, 0}, {6, 0}},
};

const int O[][4][2] = {
    {{4, 0}, {4, -1}, {5, 0}, {5, -1}},
};

const int T[][4][2] = {
    {{4, -1}, {5, 0}, {5, -1}, {6, -1}},
    {{4, -1}, {5, 0}, {5, -1}, {5, -2}},
    {{4, 0}, {5, 0}, {5, -1}, {6, 0}},
    {{4, 0}, {0, -1}, {0, -2}, {5, -1}},
};

Tetromino::Tetromino(Window* window, Image &image)
    : window(window), image(image) {
}

Tetromino::Tetromino(Window* window, Image &image, char type)
    : window(window), image(image) {
    setType(type);
}

bool Tetromino::setType(char type) {
    this->type = type = toupper(type);
    this->color = kBlue_color;
    this->turn_index = rand() % getNumOfTypeCoordinates(type);

    for (int i = 0; i < 4; i++) {
        this->coordinates[i][0] = getTypeCoordinates(type, turn_index, i, 0);
        this->coordinates[i][1] = getTypeCoordinates(type, turn_index, i, 1);
    }

    flashScreen();
}

void Tetromino::rotate(int times) {
    times = times % 4;

    for (size_t i = 0; i <= times; i++) {
        rotate(this->type);
    }
}

void Tetromino::rotate(char type) {
    /* 将方块进行顺时针旋转 90° */
    int x_dis = this->coordinates[0][0] -
                getTypeCoordinates(type, turn_index, 0, 0);
    int y_dis = this->coordinates[0][1] -
                getTypeCoordinates(type, turn_index, 0, 1);
    this->turn_index = (this->turn_index + 1) % getNumOfTypeCoordinates(type);

    int cross_board_dis_x = 0, cross_board_dis_y = 0;
    for (int i = 0; i < 4; i++) {
        this->coordinates[i][0] = x_dis +
                                  getTypeCoordinates(type, turn_index, i, 0);
        this->coordinates[i][1] = y_dis +
                                  getTypeCoordinates(type, turn_index, i, 1);
        cross_board_dis_x = std::max(cross_board_dis_x, coordinates[i][0] - 9);
    }

    if (cross_board_dis_x > 0) {
        moveLeft();
    }

    flashScreen();
}

bool Tetromino::move(string direction) {
    if (direction == "Right") {
        return moveRight();
    } else if (direction == "Left") {
        return moveLeft();
    } else if (direction == "Down") {
        return moveDown();
    }
    return false;
}

bool Tetromino::moveLeft() {
    for (size_t i = 0; i < 4; i++) {
        if (this->coordinates[i][0] == 0) {
            // 已经碰壁，无法继续左移
            return false;
        }
    }

    for (size_t i = 0; i < 4; i++) {
        this->coordinates[i][0] -= 1;
    }

    flashScreen();
    return true;
}

bool Tetromino::moveRight() {
    for (size_t i = 0; i < 4; i++) {
        if (this->coordinates[i][0] == 9) {
            // 已经碰壁，无法继续右移
            return false;
        }
    }

    for (size_t i = 0; i < 4; i++) {
        this->coordinates[i][0] += 1;
    }

    flashScreen();
    return true;
}

bool Tetromino::moveDown() {
    for (size_t i = 0; i < 4; i++) {
        if (this->coordinates[i][1] == 19) {
            // 已经碰壁，无法继续下移
            return false;
        }
    }

    for (size_t i = 0; i < 4; i++) {
        this->coordinates[i][1] += 1;
    }

    flashScreen();
    return true;
}

int Tetromino::getTypeCoordinates(char type, int turn_index, int row, int col) {
    type = toupper(type);

    switch (type) {
        case 'S':
            return S[turn_index][row][col];

        case 'Z':
            return Z[turn_index][row][col];

        case 'L':
            return L[turn_index][row][col];

        case 'J':
            return J[turn_index][row][col];

        case 'I':
            return I[turn_index][row][col];

        case 'O':
            return O[turn_index][row][col];

        case 'T':
            return T[turn_index][row][col];

        default:
            return 0;
    }
}

int Tetromino::getNumOfTypeCoordinates(char type) {
    type = toupper(type);

    switch (type) {
        case 'S':
        case 'Z':
        case 'I':
            return 2;

        case 'L':
        case 'J':
        case 'T':
            return 4;

        case 'O':
            return 1;

        default:
            return 0;
    }
}

void Tetromino::flashScreen() const {
    Image new_image = this->image; // copy a new image

    for (int i = 0; i < 4; i++) {
        int x = this->coordinates[i][0], y = this->coordinates[i][1];

        if (x >= 0 && x < kXDim && y >= 0 && y < kYDim) {
            new_image[x][y] = this->color;
        }
    }

    this->window->draw(new_image);
}

void Tetromino::mixIntoImage() {
}