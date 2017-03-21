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

#include "Clock.h"
#include "Duration.h"
#include "Font.h"
#include "Mouse.h"
#include "Renderer.h"
#include "Sprite.h"
#include "Surface.h"
#include "Text.h"
#include "Texture.h"
#include "Vector2.h"
#include "Vector2f.h"
#include "View.h"
#include "Window.h"

namespace sdl {
inline void Quit()
{
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

inline void Init()
{
    // Initialize sdl
#ifdef __EMSCRIPTEN__
    auto errCode = SDL_Init(SDL_INIT_VIDEO);
#else
    auto errCode = SDL_Init(SDL_INIT_EVERYTHING);
#endif
    if (errCode != 0) {
        std::cout << "SDL_Init failed.\n";
        printf("SDL_Init failed %s\n", SDL_GetError());
        throw 0;
    }

    // Initialize sdl_ttf
    if (TTF_Init() == -1) {
          std::cout << "TTF_Init failed.\n";
        throw 1;
    }

    // Initialize sdl_image
    const int image_flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
    const int initialized_flags = IMG_Init(image_flags);
    if ((initialized_flags & image_flags) != image_flags) {
        std::cout << "IMG_Init failed.\n";
        throw 2;
    }

    atexit(Quit);
}
}
