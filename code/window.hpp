#ifndef DRAW_HPP
#define DRAW_HPP

#include "image.hpp"
#include "SDL2/SDL.h"
#include <string>
using std::string;

class Window {
  public:
    Window(string window_name, int width = 400, int height = 800);
    ~Window();
    bool draw(string bmp_file_name);
    bool draw(const Image &image);
    SDL_Window* getWindow() {
        return window;
    }
    SDL_Surface* getSurface() {
        return surface;
    }

  private:
    SDL_Window* window;
    SDL_Surface* surface;
    SDL_Texture* texture;
    // SDL_Rect rect;
    SDL_Renderer* renderer;
};

#endif