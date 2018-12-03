#ifndef DRAW_HPP
#define DRAW_HPP

#include "SDL2/SDL.h"
#include <string>
using std::string;

class Window {
public:
    Window() {}
    ~Window() {}
    bool draw(SDL_Surface*, string bmp_file_name);
private:
};

#endif