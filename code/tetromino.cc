#include "tetromino.hpp"

#include <string>
#include <vector>
#include <stdint.h>
#include <algorithm>
#include <iostream>
using std::make_pair;
using std::vector;

Tetromino::Tetromino() {
    initAllTypesCoordinates();
}

Tetromino::Tetromino(char type) {
    initAllTypesCoordinates();
    setSquares(type);
};

bool Tetromino::setSquares(char type) {
    this->type = type = toupper(type);
    this->turn_index = rand() % 4;
    int x_dis = INT32_MAX, y_dis = INT32_MAX;
    for (int i = 0; i < 4; i++) {
        int tmp = (type == 'I' and this->turn_index % 2 == 1 ? 7 : 6);
        x_dis = std::min(x_dis, tmp - 
                this->all_types_init_coordinates[type][this->turn_index][i][0]);
        y_dis = std::min(y_dis, 19 - 
                this->all_types_init_coordinates[type][this->turn_index][i][1]);
    }
}

void Tetromino::rotate(int times) {
    times = times % 4;

    for (size_t i = 0; i < times; i++) {
        rotate(this->type);
    }
}

void Tetromino::rotate(char type) {
    /* 将方块进行顺时针旋转 90° */
    int x_dis = this->coordinates[0][0] - 
                this->all_types_init_coordinates[type][this->turn_index][0][0];
    int y_dis = this->coordinates[0][1] -
                this->all_types_init_coordinates[type][this->turn_index][0][1];
    this->turn_index = (this->turn_index + 1) % 4;

    for (int i = 0; i < 4; i++) {
        this->coordinates[i][0] = x_dis + 
                this->all_types_init_coordinates[type][this->turn_index][i][0];
        this->coordinates[i][1] = y_dis + 
                this->all_types_init_coordinates[type][this->turn_index][i][1];
    }
}

bool Tetromino::moveLeft() {
    for (size_t i = 0; i < 4; i++) {
        if (this->coordinates[i][0] == 0) { // 已经碰壁，无法继续左移
            return false;
        }
    }

    for (size_t i = 0; i < 4; i++) {
        this->coordinates[i][0] -= 1;
    }

    return true;
}

bool Tetromino::moveRight() {
    for (size_t i = 0; i < 4; i++) {
        if (this->coordinates[i][0] == 9) { // 已经碰壁，无法继续右移
            return false;
        }
    }

    for (size_t i = 0; i < 4; i++) {
        this->coordinates[i][0] += 1;
    }

    return true;
}

bool Tetromino::moveDown() {
    for (size_t i = 0; i < 4; i++) {
        if (this->coordinates[i][0] == 9) { // 已经碰壁，无法继续下移
            return false;
        }
    }

    for (size_t i = 0; i < 4; i++) {
        this->coordinates[i][1] += 1;
    }

    return true;
}

void Tetromino::initAllTypesCoordinates() {
    int S[][4][2] = {
        {{0, 0}, {1, 0}, {1, 1}, {2, 1}},
        {{0, 1}, {0, 2}, {1, 0}, {1, 1}},
    };

    int Z[][4][2] = {
        {{0, 1}, {1, 0}, {1, 1}, {2, 0}},
        {{0, 0}, {0, 1}, {1, 1}, {1, 2}},
    };

    int L[][4][2] = {
        {{0, 0}, {0, 1}, {0, 2}, {1, 0}},
        {{0, 0}, {0, 1}, {1, 1}, {2, 1}},
        {{0, 2}, {1, 0}, {1, 1}, {1, 2}},
        {{0, 0}, {1, 0}, {2, 0}, {2, 1}},
    };

    int J[][4][2] = {
        {{0, 0}, {1, 0}, {1, 1}, {1, 2}},
        {{0, 0}, {0, 1}, {1, 0}, {2, 0}},
        {{0, 0}, {0, 1}, {0, 2}, {1, 2}},
        {{0, 1}, {1, 1}, {2, 0}, {2, 1}},
    };

    int I[][4][2] = {
        {{0, 0}, {0, 1}, {0, 2}, {0, 3}},
        {{0, 0}, {1, 0}, {2, 0}, {3, 0}},
    };

    int O[][4][2] = {
        {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
    };

    int T[][4][2] = {
        {{0, 1}, {1, 0}, {1, 1}, {2, 1}},
        {{0, 1}, {1, 0}, {1, 1}, {1, 2}},
        {{0, 0}, {1, 0}, {1, 1}, {2, 0}},
        {{0, 0}, {0, 1}, {0, 2}, {1, 1}},
    };

    this->all_types_init_coordinates.insert(make_pair('S', S));
    this->all_types_init_coordinates.insert(make_pair('Z', Z));
    this->all_types_init_coordinates.insert(make_pair('L', L));
    this->all_types_init_coordinates.insert(make_pair('J', J));
    this->all_types_init_coordinates.insert(make_pair('I', I));
    this->all_types_init_coordinates.insert(make_pair('O', O));
    this->all_types_init_coordinates.insert(make_pair('T', T));
}