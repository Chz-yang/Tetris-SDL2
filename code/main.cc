#include "RGB.hpp"
#include "bmp.hpp"
#include "window.hpp"
#include <SDL2/SDL.h>
#include <iostream>
using std::cout;
using std::endl;
const int kXDim = 10, kYDim = 20;

bool isGameOver();

int main(int argc, char const* argv[]) {
    RGB **image = (RGB**)malloc(sizeof(RGB*) * kXDim);
    for (int x = 0; x < kXDim; x++) {
        image[x] = (RGB*)malloc(sizeof(RGB) * kYDim);
        for (int y = 0; y < kYDim; y++) {
            image[x][y] = kBlack_color;
        }
    }
    // image[4][0] = kBlue_color;
    // image[5][0] = kBlue_color;

    Bitmap test(400, 800);
    test.convertToBmp("../resource/img/test.bmp", image, 10, 20);

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* g_window = NULL;
    SDL_Surface* g_screen_surface = NULL;
    g_window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, 
                           SDL_WINDOWPOS_UNDEFINED, 400, 800, SDL_WINDOW_SHOWN);
    g_screen_surface = SDL_GetWindowSurface(g_window);

    Window window;
    window.draw(g_screen_surface, "../resource/img/test.bmp");

    SDL_UpdateWindowSurface(g_window);
    SDL_Delay(1000);
    SDL_DestroyWindow(g_window);
    SDL_Quit();
    
    for (int x = 0; x < kXDim; x++) {
        free(image[x]);
    }
    free(image);

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