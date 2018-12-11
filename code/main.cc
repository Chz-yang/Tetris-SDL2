#include "RGB.hpp"
#include "bmp.hpp"
#include "window.hpp"
#include "image.hpp"
#include "tetromino.hpp"
#include <SDL2/SDL.h>
#include <unistd.h>
#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;

bool isGameOver();
bool eliminateLine(Image* image, Window* window);
void imageColMoveDown(Image* image, int x, int y);

int main(int argc, char const* argv[]) {
    Image image;
    Window window("Tetris");

    SDL_Event my_event;
    bool quit = false;
    int count = 0;
    int flag = 0;
    Tetromino tetromino(&window, &image);
    tetromino.newTetromino();

    while (!quit) {
        if (SDL_PollEvent(&my_event)) {
            switch (my_event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;

                case SDL_KEYDOWN:
                    string key = SDL_GetKeyName(my_event.key.keysym.sym);
                    flag = tetromino.move(key);
                    break;
            }
        }

        usleep(5 * 1000);
        count++;

        if (count >= 100) {
            flag = tetromino.move("Down");
            count = 0;
        }

        if (flag == 2) {
            eliminateLine(&image, &window);
            tetromino.newTetromino();

            while (SDL_PollEvent(&my_event))
                ; // clear event queue

            flag = 0;
            count = 0;
        }
    }

    return 0;
}

bool eliminateLine(Image* image, Window* window) {
    int line_index = -1;

    for (int y = kYDim - 1; y >= 0; y--) {
        bool flag = true;

        for (int x = 0; x < kXDim; x++) {
            if ((*image)[x][y] == kBlack_color) {
                flag = false;
                break;
            }
        }

        if (flag) {
            // 从屏幕底到上，找到第一个可以被消除的行
            line_index = y;
            break;
        } else if (flag == false && y == 0) {
            return false;
        }
    }

    for (int x = 0; x < kXDim; x++) {
        // 消除该行
        (*image)[x][line_index] = kBlack_color;
    }

    window->draw(*image); // 刷新一次屏幕
    usleep(100 * 1000);

    for (int x = 0; x < kXDim; x++) {
        // 把(line_index - 1)该行及该行以上的方块往下移动一行
        imageColMoveDown(image, x, line_index - 1);
    }

    window->draw(*image); // 刷新一次屏幕
    usleep(400 * 1000);

    eliminateLine(image, window);

    vector<int> can_move_down_x_vector;
    for (int x = 0; x < kXDim; x++) {
        can_move_down_x_vector.push_back(x);
    }

    /* 将可以下落的方块一行一行的落下 */
    while (!can_move_down_x_vector.empty() && line_index < kYDim - 1) {
        int size = can_move_down_x_vector.size();

        for (int i = 0; i < size; i++) {
            int x = can_move_down_x_vector.back();
            can_move_down_x_vector.pop_back();
            if ((*image)[x][line_index + 1] == kBlack_color &&
                    (*image)[x][line_index] != kBlack_color) {
                imageColMoveDown(image, x, line_index);
                can_move_down_x_vector.insert(
                    can_move_down_x_vector.begin(), x);
            }
        }

        if (can_move_down_x_vector.empty() == false) {
            window->draw(*image);
            usleep(500 * 1000);
        }
        line_index += 1;
    }

    return eliminateLine(image, window);
}

void imageColMoveDown(Image* image, int x, int y) {
    /* 将x这一列，从y这一行起的方块全往下移动一行 */
    for (int y0 = y; y0 >= 0; y0--) {
        (*image)[x][y0 + 1] = (*image)[x][y0];
    }

    (*image)[x][0] = kBlack_color;
}

bool isGameOver(const RGB imgage[][kXDim]) {
    /* 方块触顶，游戏结束。 */
    for (int y = 0; y < kYDim; y++) {
        if (imgage[y][0] != kBlack_color) {
            return true;
        }
    }

    return false;
}