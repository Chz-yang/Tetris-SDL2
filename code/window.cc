#include "window.hpp"
#include "bmp.hpp"

Window::Window(string window_name, int width, int height) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    this->window = SDL_CreateWindow(window_name.c_str(),
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    width, height,
                                    SDL_WINDOW_SHOWN);
    this->renderer = SDL_CreateRenderer(this->window, 
                                        -1, 
                                        SDL_RENDERER_ACCELERATED | 
                                        SDL_RENDERER_PRESENTVSYNC);
    initWindow();
}

Window::~Window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(this->window);
    TTF_Quit();
    SDL_Quit();
}

bool Window::draw(string bmp_file_name, int x, int y, int w, int h) {
    SDL_Surface* bmp_surface = NULL;
    bmp_surface = SDL_LoadBMP(bmp_file_name.c_str());

    if (bmp_surface == NULL) {
        // bmp 文件不存在
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, bmp_surface);
    // SDL_RenderClear(renderer);
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_RenderPresent(renderer);
    SDL_FreeSurface(bmp_surface);
    SDL_DestroyTexture(texture);
    return true;
}

bool Window::draw(const Image &image, int x, int y) {
    static string tmp_bmp_file_name = "../resource/img/temple.bmp";
    Bitmap bmp(400, 800);
    bmp.convertToBmp(tmp_bmp_file_name, image.getPixels(), 10, 20);

    if (draw(tmp_bmp_file_name, x, y)) {
        return true;
    } else {
        return false;
    }
}

bool Window::write(string text, int font_size, int x, int y, SDL_Color color) {
    TTF_Font* font = nullptr;
    font = TTF_OpenFont("../resource/TTF/times.ttf", font_size);
    SDL_Color text_color = color;
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), text_color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect font_rect = {x, y};
    font_rect.w = text.length() * 20; font_rect.h = 60;
    if (x == 0 && y == 0) {
        x = 430 + (145 - 15 * text.length()) / 2;
        y = 200 + (290 - 200 - 45) / 2;
        font_rect = {x, y, int(text.length() * 15), 45};
        SDL_RenderClear(renderer);
        initWindow();
    }
    SDL_RenderCopy(renderer, texture, NULL, &font_rect);
    SDL_RenderPresent(renderer);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
    return true;
}

bool Window::setBackground(string file_name) {
    draw(file_name, 0, 0, 600, 800);
}

void Window::initWindow() {
    setBackground();
    this->write("Score", 128, 450, 150);
}