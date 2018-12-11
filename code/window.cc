#include "window.hpp"
#include "bmp.hpp"

Window::Window(string window_name, int width, int height) {
    SDL_Init(SDL_INIT_VIDEO);
    this->window = SDL_CreateWindow(window_name.c_str(),
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    width, height,
                                    SDL_WINDOW_SHOWN);
    this->renderer = SDL_CreateRenderer(this->window, 
                                        -1, 
                                        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

Window::~Window() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

bool Window::draw(string bmp_file_name) {
    SDL_Surface* bmp_surface = NULL;
    bmp_surface = SDL_LoadBMP(bmp_file_name.c_str());

    if (bmp_surface == NULL) {
        // bmp 文件不存在
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, bmp_surface);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_FreeSurface(bmp_surface);
    SDL_DestroyTexture(texture);
    return true;
}

bool Window::draw(const Image &image) {
    static string tmp_bmp_file_name = "../resource/img/temple.bmp";
    Bitmap bmp(400, 800);
    bmp.convertToBmp(tmp_bmp_file_name, image.getPixels(), 10, 20);

    if (draw(tmp_bmp_file_name)) {
        return true;
    } else {
        return false;
    }
}