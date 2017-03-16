#pragma once


#ifdef __APPLE__
#ifdef _SDL2
// waf
// #include "SDL.h"
#include <SDL_ttf.h>
#else
// #include "SDL2/SDL.h"
#include "SDL2_ttf/SDL_ttf.h"
#endif
#else
// #include "SDL.h"
#include <SDL_ttf.h>
#endif

#include "Util.h"
#include <string>

namespace sdl {
class Font {
    friend class Text;

private:
    TTF_Font* _font;
    std::string _file;
    int _size;

public:
    Font()
        : _font(nullptr)
    {
    }

    Font(std::string file, int pt_size)
        : _font(nullptr)
        , _file(file)
        , _size(pt_size)
    {
        _font = TTF_OpenFont(file.c_str(), pt_size);
        if (_font == nullptr)
            Throw();
    }

    Font(Font&& font)
    {
        _font = font._font;
        _file = font._file;
        _size = font._size;
        font._font = nullptr;
    }
    Font(const Font& font)
    {
        _font = TTF_OpenFont(font._file.c_str(), font._size);
        if (_font == nullptr)
            Throw();
    }

    Font& operator=(const Font& font)
    {
        _font = TTF_OpenFont(font._file.c_str(), font._size);
        if (_font == nullptr)
            Throw();
        return *this;
    }

    ~Font()
    {
        if (_font != nullptr)
            TTF_CloseFont(_font);
    }
};
}
