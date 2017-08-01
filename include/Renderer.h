#pragma once
#ifdef __APPLE__
#ifdef _SDL2
// waf
#include "SDL.h"
#else
#include "SDL2/SDL.h"
#endif
#else
#include "SDL.h"
#endif

#include "Color.h"
#include "Texture.h"
#include "Util.h"
#include "View.h"
#include "Window.h"
#include <set>
#include <stdint.h>

#include <memory>

// #include <mathfu/vector.h>

namespace sdl {
    
class Sprite;
class Surface;
class Text;
class Vector2f;
    
class Renderer {
private:
    typedef std::unique_ptr<Texture> texture_ptr;
    SDL_Renderer* _ren;
    std::set<texture_ptr> _textures;
    View _view;

public:
    Renderer(SDL_Window* win, const uint32_t flags)
        : _ren(nullptr)
    {
        _ren = SDL_CreateRenderer(win, -1, flags);
        if (_ren == nullptr) {
            printf("Could not create renderer\n");
            Throw();
        }
    }

    Renderer(const Renderer& other) = delete;
    Renderer& operator=(const Renderer& other) = delete;

    ~Renderer()
    {
        if (_ren != nullptr)
            SDL_DestroyRenderer(_ren);
    }

    Texture* CreateTexture(const int w, const int h);
    Texture* CreateTexture(const int w, const int h, const int access);
    Texture* CreateTexture(const Surface& surface);
    Texture* CreateTexture(const std::string& file);

    void Clear() const;
    void clear(const Color c) const;
    void Draw(Sprite& sprite) const;
    
    void Draw(Text& text) const;
    void draw(Rect& rect, const Color c = sdl::Colors::White) const;

    void drawLine(const Vec2& a, const Vec2& b, Color c) const;

    void drawLines(const SDL_Point* points, int count);

    template <std::size_t N>
    inline void drawLines(const std::array<SDL_Point*, N>& points)
    {
        drawLines(points.data(), points.size());
    }

    void drawCircle(const Vec2& pos, float radius, Color col);

    void Present() const;

    View* GetView() { return &_view; }
    void SetView(const View& view) { _view = view; }

private:
    void setRenderColor(const Color c) const;
    Texture* AddTexture(texture_ptr texture);
};
}
