#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
using namespace std;

int main() {
    // TTF_Init();
    // TTF_Font* font = TTF_OpenFont("times.ttf", 24);
    // SDL_Color text_color = {255, 255, 255};
    // char text[] = "testing";
    // SDL_Surface* surface = TTF_RenderText_Solid(font, text, text_color);
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("testing",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          400, 800,
                                          SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, 
                                                -1, 
                                                SDL_RENDERER_ACCELERATED | 
                                                SDL_RENDERER_PRESENTVSYNC);
    static string bmp_file_name = "../resource/img/background.bmp";
    SDL_Surface* bmp_surface = NULL;
    bmp_surface = SDL_LoadBMP(bmp_file_name.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, bmp_surface);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_RenderPresent(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(3000);
    SDL_FreeSurface(bmp_surface);
    SDL_DestroyTexture(texture);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
 
}