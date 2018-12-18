#ifndef DRAW_HPP
#define DRAW_HPP

#include "image.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <string>
using std::string;

class Window {
  public:
    Window(string window_name, int width = 600, int height = 800);
    ~Window();
    bool draw(string bmp_file_name, int x = 0, int y = 0, int w = 400, int h = 800);
    bool draw(const Image &image, int x = 0, int y = 0);
    bool write(string text, int font_size = 128, int x = 0, int y = 0, SDL_Color color = {0, 0, 255});
    SDL_Window* getWindow() {
        return window;
    }

  private:
    bool setBackground(string file_name = "../resource/img/background.bmp");
    void initWindow();
  private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif