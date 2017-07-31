#pragma once

#ifdef __APPLE__
#ifdef _SDL2
// waf
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#else
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_ttf/SDL_ttf.h"
#endif
#else

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
// #include <SDL2/SDL_ttf.h>
#endif


namespace sdl {
class Color {
private:
    SDL_Color _color;

public:
    Color()
        : Color(255, 255, 255, 255)
    {
    }
    Color(const int r, const int g, const int b)
        : Color(r, g, b, 255)
    {
    }
    Color(const int r, const int g, const int b, const int a)
    {
        _color.r = r;
        _color.g = g;
        _color.b = b;
        _color.a = a;
    }

    SDL_Color GetColor() const { return _color; }
    int R() const { return _color.r; }
    int G() const { return _color.g; }
    int B() const { return _color.b; }
    int A() const { return _color.a; }
};
namespace Colors {
    static Color White{ 255, 255, 255, 255 };
    static Color Red{ 255, 0, 0, 255 };
    static Color Green{ 0, 255, 0, 255 };
    static Color Blue{ 0, 0, 255, 255 };
    static Color Black{ 0, 0, 0, 255 };
}
}
