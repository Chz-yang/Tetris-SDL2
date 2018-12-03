#include "window.hpp"

bool Window::draw(SDL_Surface *surface, string bmp_file_name) {
    SDL_Surface *bmp_surface = NULL;
    bmp_surface = SDL_LoadBMP(bmp_file_name.c_str());
    if (bmp_surface == NULL) {
        // bmp 文件不存在
        return false;
    }

    SDL_BlitSurface(bmp_surface, NULL, surface, NULL);
    SDL_FreeSurface(bmp_surface);
    return true;
}