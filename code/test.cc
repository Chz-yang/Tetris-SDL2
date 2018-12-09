#include "SDL2/SDL.h"
#include <iostream>
using namespace std;

SDL_Texture* loadTexture(const string &file, SDL_Renderer* ren) {
    SDL_Texture *texture = nullptr;
    SDL_Surface *img = nullptr;
    img = SDL_LoadBMP(file.c_str());
    if (img == nullptr) {cout << "false\n";}
    texture = SDL_CreateTextureFromSurface(ren, img);
    SDL_FreeSurface(img);
    if (texture == nullptr) {cout << "false\n";}
    // SDL_RenderCopy(ren, texture, NULL, NULL);
    // SDL_RenderPresent(ren);
    return texture;
}

int main() {
    string window_name = "Test";
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow(window_name.c_str(),
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    400, 800,
                                    SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 
                                        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Texture* background = loadTexture("../resource/img/background.bmp", renderer);
    if (background == nullptr) {
        cout << "!\n";
    }
    SDL_RenderCopy(renderer, background, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(10000);
    
    // SDL_Texture* image = loadTexture("../resource/img/tetromino_blue.bmp", renderer);

    // SDL_Rect dst;
    // dst.x = 0; dst.y = 0;
    // SDL_QueryTexture(background, NULL, NULL, &dst.w, &dst.y);
    // SDL_RenderClear(renderer);
    
    // SDL_RenderCopy(renderer, image, NULL, &dst);

    // SDL_FreeSurface(image);
    // SDL_DestroyTexture(image);
    SDL_DestroyTexture(background);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


// #include "bitmap_image.hpp"
// #include "RGB.hpp"

// int main(int argc, char const *argv[])
// {
//     bitmap_image img;
//     img.setwidth_height(400, 800);
//     for (int i = 0; i < 400; i++) {
//         for (int j = 0; j < 800; j++) {
//             img.set_pixel(i, j, kBlack_color);
//         }
//     }

//     img.save_image("../resource/img/background.bmp");
//     return 0;
// }


// int main() {
//     bitmap_image img;
//     img.setwidth_height(40, 40);
//     for (int i = 0; i < 40; i++) {
//         for (int j = 0; j < 40; j++) {
//             img.set_pixel(i, j, kBlue_color);
//         }
//     }
//     for (int i = 0; i < 2; i++) {
//         for (int j = 0; j < 40; j++) {
//             img.set_pixel(i, j, kWhite_color);
//             img.set_pixel(39 - i, j, kWhite_color);
//         }
//     }

//     for (int i = 0; i < 40; i++) {
//         for (int j = 0; j < 2; j++) {
//             img.set_pixel(i, j, kWhite_color);
//             img.set_pixel(i, 39 - j, kWhite_color);
//         }
//     }
//     img.save_image("../resource/img/tetromino_blue.bmp");
// }