#include "tetromino.hpp"
#include <string>
#include <vector>
#include <stdint.h>
#include <algorithm>
#include <iostream>
using std::make_pair;
using std::vector;

const int S[][4][2] = {
    {{4, 0}, {5, 0}, {5, -1}, {6, -1}},
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
    {{4, 1}, {4, 0}, {4, -1}, {4, -2}},
    {{3, 0}, {4, 0}, {5, 0}, {6, 0}},
};

const int O[][4][2] = {
    {{4, 0}, {4, -1}, {5, 0}, {5, -1}},
};

const int T[][4][2] = {
    {{4, -1}, {5, 0}, {5, -1}, {6, -1}},
    {{4, -1}, {5, 0}, {5, -1}, {5, -2}},
    {{4, 0}, {5, 0}, {5, -1}, {6, 0}},
    {{4, 0}, {4, -1}, {4, -2}, {5, -1}},
};

Tetromino::Tetromino(Window* window, Image *image)
    : window(window), image(image) {
    srand(time(NULL));    
}

Tetromino::Tetromino(Window* window, Image *image, char type)
    : window(window), image(image) {
    setType(type);
    srand(time(NULL));
}

bool Tetromino::setType(char type) {
    this->type = type = toupper(type);
    this->color = kBlue_color;
    this->turn_index = rand() % getNumOfTypeCoordinates(type);

    for (int i = 0; i < 4; i++) {
        this->coordinates[i][0] = getTypeCoordinates(type, turn_index, i, 0);
        this->coordinates[i][1] = getTypeCoordinates(type, turn_index, i, 1);
        if (this->coordinates[i][1] >= 0 && 
            isValid(this->coordinates[i][0], this->coordinates[i][1]) == 2) {
            return false;
        }
    }

    return true;
}

int Tetromino::rotate() {
    /* 将方块进行顺时针旋转 90° */
    int new_turn_index;
    int new_coordinates[4][2];
    int x_dis = this->coordinates[0][0] -
                getTypeCoordinates(type, turn_index, 0, 0);
    int y_dis = this->coordinates[0][1] -
                getTypeCoordinates(type, turn_index, 0, 1);
    new_turn_index = (this->turn_index + 1) % getNumOfTypeCoordinates(type);

    int cross_board_dis_x = 0, cross_board_dis_y = 0;
    for (int i = 0; i < 4; i++) {
        new_coordinates[i][0] = x_dis +
                                getTypeCoordinates(type, new_turn_index, i, 0);
        new_coordinates[i][1] = y_dis +
                                getTypeCoordinates(type, new_turn_index, i, 1);
        cross_board_dis_x = std::max(cross_board_dis_x, coordinates[i][0] - 9);
        if (isValid(new_coordinates[i][0], new_coordinates[i][1]) != 0) {
            // can not rotate, return false
            return 1;
        }
    }

    // can rotate, accept this rotate
    this->turn_index = new_turn_index;
    for (int i = 0; i < 4; i++) {
        this->coordinates[i][0] = new_coordinates[i][0];
        this->coordinates[i][1] = new_coordinates[i][1];
    }

    while (cross_board_dis_x > 0) {
        moveLeft();
        cross_board_dis_x--;
    }

    return 0;
}

int Tetromino::move(string key) {
    int flag = 0;
    if (key == "Right") {
        // move right
        flag = moveRight();
    } else if (key == "Left") {
        // move left
        flag = moveLeft();
    } else if (key == "Down") {
        // move down
        flag = moveDown();
    } else if (key == "Space") { 
        // rotate
        flag = rotate();
    }
    if (flag == 0) {
        Image new_image(*this->image);
        flashScreen(&new_image);
    } else if (flag == 2) {
        // can not move down 
        flashScreen(this->image);
    }

    return flag;
}

int Tetromino::moveLeft() {
    for (size_t i = 0; i < 4; i++) {
        int x = this->coordinates[i][0], y = this->coordinates[i][1];
        if (x == 0 || isValid(x - 1, y) == 2) {
            // 已经碰壁，无法继续左移
            return 1;
        }
    }

    for (size_t i = 0; i < 4; i++) {
        this->coordinates[i][0] -= 1;
    }

    return 0;
}

int Tetromino::moveRight() {
    for (size_t i = 0; i < 4; i++) {
        int x = this->coordinates[i][0], y = this->coordinates[i][1];
        if (x == 9 || isValid(x + 1, y) == 2) {
            // 已经碰壁，无法继续右移
            return 1;
        }
    }

    for (size_t i = 0; i < 4; i++) {
        this->coordinates[i][0] += 1;
    }

    return 0;
}

int Tetromino::moveDown() {
    for (size_t i = 0; i < 4; i++) {
        int x = this->coordinates[i][0], y = this->coordinates[i][1];
        if (isValid(x, y + 1) == 2) {
            return 2;
        } else if (y == 19) {
            // 已经碰壁，无法继续下移
            return 2;
        }
    }

    for (size_t i = 0; i < 4; i++) {
        this->coordinates[i][1] += 1;
    }

    return 0;
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

void Tetromino::flashScreen(Image *img) {
    for (int i = 0; i < 4; i++) {
        int x = this->coordinates[i][0], y = this->coordinates[i][1];

        if (x >= 0 && x < kXDim && y >= 0 && y < kYDim) {
            (*img)[x][y] = this->color;
        }
    }

    this->window->draw(*img);
}

int Tetromino::isValid(int x, int y) {
    if (x < 0 || x >= kXDim || y >= kYDim) {
        return 1;
    }

    if ((*this->image)[x][y] != kBlack_color) {
        return 2;
    }

    return 0;
}

bool Tetromino::newTetromino() {
    static char tetromino_type[] = {'S', 'Z', 'L', 'J', 'I', 'O', 'T'};
    int type_count = sizeof(tetromino_type) / sizeof(char);
    int type_index = rand() % type_count;
    if (setType(tetromino_type[type_index])) {
        Image new_image = Image(*this->image);
        flashScreen(&new_image);
        return true;
    } else {
        return false;
    }
}