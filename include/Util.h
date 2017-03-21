#pragma once
#include <iostream>
#include "Vector2.h"

namespace sdl {
typedef SDL_Rect Rect;

inline Rect MakeRect(int x, int y, int w, int h) {
    Rect ret;
    ret.x = x;
    ret.y = y;
    ret.w = w;
    ret.h = h;
    return ret;
}

inline Rect makeRect(const Vec2& pos, const Vec2& size)
{
    return MakeRect(pos.x(), pos.y(), size.x(), size.y());
}

inline std::ostream &operator<<(std::ostream &os, const Rect &rect) {
    os << "[" << rect.x << ", "
       << rect.y << ", "
       << rect.w << ", "
       << rect.h << std::endl;
    return os;
}

inline void Throw() {
    std::cout << SDL_GetError() << std::endl;
    throw 0;
}
}
