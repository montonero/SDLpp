#pragma once
#ifdef __APPLE__
#ifdef _SDL2
// waf
#include "SDL.h"
#include <SDL_image.h>
#else
#include "SDL2/SDL.h"
#include "SDL2_Image/SDL_image.h"
#endif
#else
#include "SDL.h"
#include <SDL_image.h>
#endif

#include <string>
#include "Util.h"

namespace sdl {
class Texture;
class Surface {
    friend class Texture;
private:
    SDL_Surface *_surface;
public:
    Surface () : _surface(nullptr) {}
    Surface(const std::string &file) {
        _surface = IMG_Load(file.c_str());
        if (_surface == nullptr) {
            Throw();
        }
    }

    Surface(const Surface &other) = delete;
    Surface &operator=(const Surface &other) = delete;

    ~Surface() {
        if (_surface != nullptr) SDL_FreeSurface(_surface);
    }
};
}
