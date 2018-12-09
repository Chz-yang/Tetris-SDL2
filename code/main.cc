#include "RGB.hpp"
#include "bmp.hpp"
#include "window.hpp"
#include "image.hpp"
#include "tetromino.hpp"
#include <SDL2/SDL.h>
#include <unistd.h>
#include <iostream>
using std::cout;
using std::endl;

bool isGameOver();

int main(int argc, char const* argv[]) {
    Image image;
    Window window("Tetris");

    Tetromino tetromino(&window, image);
    SDL_Event my_event;
    tetromino.setType('J');
    bool quit = false;
    int count = 0;
    while (!quit) {
        if (SDL_PollEvent(&my_event)) {
            switch (my_event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    string key = SDL_GetKeyName(my_event.key.keysym.sym);
                    if (key != "Space") {
                        tetromino.move(key);
                    } else {
                        tetromino.rotate();
                    }
                    break;
            }
        } else {
            usleep(50 * 1000);
            count++;
            if (count == 20) {
                tetromino.move("Down");
                count = 0;
            }
        }
    }

    return 0;
}

bool isGameOver(const RGB imgage[][kXDim]) {
    /* 方块触顶，游戏结束。 */
    for (int y = 0; y < kYDim; y++) {
        if (imgage[y][19] != kBlack_color) {
            return true;
        }
    }

    return false;
}