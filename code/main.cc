#include "RGB.hpp"
#include "bmp.hpp"
#include "window.hpp"
#include "image.hpp"
#include "tetromino.hpp"
#include <SDL2/SDL.h>
#include <unistd.h>
#include <vector>
#include <set>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;

void gameOver(Image* image, Window* window);
bool eliminateLine(Image* image, Window* window, int &count);
void imageColMoveDown(Image* image, int x, int y);
void updateScore(Window* window, int count);

int main(int argc, char const* argv[]) {
    Image image;
    Window window("Tetris");

    SDL_Event my_event;
    bool quit = false;
    int count = 0;
    int flag = 0;
    Tetromino tetromino(&window, &image);
    tetromino.newTetromino();
    updateScore(&window, 0);

    std::set<string> valid_key_set;
    valid_key_set.insert("Left");
    valid_key_set.insert("Right");
    valid_key_set.insert("Down");
    valid_key_set.insert("Space");
    valid_key_set.insert("Return");

    bool invalid_key_down = false;
    bool pause_flag = false;
    string key;
    while (!quit) {
        if (SDL_PollEvent(&my_event)) {
            switch (my_event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;

                case SDL_KEYDOWN:
                    if (invalid_key_down) {break;}
                    key = SDL_GetKeyName(my_event.key.keysym.sym);

                    if (key == "Space" || 
                        valid_key_set.find(key) == valid_key_set.end()) {
                        invalid_key_down = true;

                    } else if (key == "Return") {
                        pause_flag = !pause_flag;
                        if (pause_flag == true) {
                            SDL_Color color = {255, 0, 0};
                            window.write("\"Pause!\"", 128, 125, 300, color);
                        }
                    }

                    if (pause_flag == false) {
                        flag = tetromino.move(key);
                    }
                    break;

                case SDL_KEYUP:
                    invalid_key_down = false;
                    break;
            }
        }

        if (pause_flag) {continue;} 

        usleep(5 * 1000);
        count++;

        if (count >= 100) {
            flag = tetromino.move("Down");
            count = 0;
        }

        if (flag == 2) {
            int count = 0;
            eliminateLine(&image, &window, count);
            if (count > 0) {updateScore(&window, count);}

            if (tetromino.newTetromino() == false) {
                gameOver(&image, &window);
                quit = true;
            }

            // clear event queue
            while (SDL_PollEvent(&my_event)) {
                ;
            }

            flag = 0;
            count = 0;
        }
    }

    return 0;
}

void updateScore(Window* window, int count) {
    static int score = 0;
    score += pow(2, count - 1);
    window->write(std::to_string(score));
}

bool eliminateLine(Image* image, Window* window, int &count) {
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
            count += 1;
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

    eliminateLine(image, window, count);

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

    return eliminateLine(image, window, count);
}

void imageColMoveDown(Image* image, int x, int y) {
    /* 将x这一列，从y这一行起的方块全往下移动一行 */
    for (int y0 = y; y0 >= 0; y0--) {
        (*image)[x][y0 + 1] = (*image)[x][y0];
    }

    (*image)[x][0] = kBlack_color;
}

void gameOver(Image* image, Window* window) {
    /* 方块触顶，游戏结束。 */
    static int direction[][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    cout << "Game Over!\n";
    int x = -1, y = 0;
    int direction_index = 0;
    int x_left = 0, x_right = kXDim - 1, y_up = 1, y_down = kYDim - 1;
    for (int i = 0; i < kXDim * kYDim; i++) {
        x += direction[direction_index][0];
        y += direction[direction_index][1];
        (*image)[x][y] = kBlue_color;
        window->draw(*image);
        usleep(1000);

        if (direction_index == 0 && x == x_right) {
            direction_index = (direction_index + 1) % 4;
            x_right -= 1;
        } else if (direction_index == 1 && y == y_down) {
            direction_index = (direction_index + 1) % 4;
            y_down -= 1;
        } else if (direction_index == 2 && x == x_left) {
            direction_index = (direction_index + 1) % 4;
            x_left += 1;
        } else if (direction_index == 3 && y == y_up) {
            direction_index = (direction_index + 1) % 4;
            y_up += 1;
        }
    }

    Image black_background;
    for (int i = 0; i < 6; i++) {
        window->draw(*image);
        usleep(100 * 1000);
        window->draw(black_background);
        usleep(100 * 1000);
    }
}