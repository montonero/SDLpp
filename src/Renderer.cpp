#include "Renderer.h"
#include "Sprite.h"
#include "Surface.h"
#include "Text.h"
#include "Texture.h"
#include "Vector2f.h"

#include <cmath> // for circle

namespace sdl {
Texture* Renderer::CreateTexture(const int w, const int h)
{
    texture_ptr tmp{ new Texture(_ren, w, h) };
    return AddTexture(std::move(tmp));
}

Texture* Renderer::CreateTexture(const int w, const int h, const int access)
{
    texture_ptr tmp{ new Texture(_ren, w, h, access) };
    return AddTexture(std::move(tmp));
}

Texture* Renderer::CreateTexture(const std::string& file)
{
    texture_ptr tmp{ new Texture(_ren, file) };
    return AddTexture(std::move(tmp));
}

Texture* Renderer::CreateTexture(const Surface& surface)
{
    texture_ptr tmp{ new Texture(_ren, surface) };
    return AddTexture(std::move(tmp));
}

void Renderer::Clear() const { SDL_RenderClear(_ren); }

void Renderer::clear(const Color c) const
{
    setRenderColor(c);
    Clear();
}

void Renderer::Draw(Sprite& sprite) const { sprite.Draw(_view); }

void Renderer::Draw(Text& text) const { text.Draw(_ren, _view); }

void Renderer::draw(Rect& rect, const Color c) const
{
    setRenderColor(c);
    SDL_RenderFillRect(_ren, &rect);
}

void Renderer::drawLine(const Vec2& a, const Vec2& b, Color c) const
{
    setRenderColor(c);
    SDL_RenderDrawLine(_ren, a.x(), a.y(), b.x(), b.y());
}

void Renderer::drawLines(const SDL_Point* points, int count)
{
    SDL_RenderDrawLines(_ren, points, count);
}

void Renderer::drawCircle(const Vec2& pos, float radius, Color col)
{
    const double PI  =3.141592653589793238463;
    const float  PI_F=3.14159265358979f;

    static const unsigned kCircleSegmentsNum	= 72;
    static const float kCircleTheta 		= 2.0 * PI_F / (float)kCircleSegmentsNum;
    static const float kCircleTanFactor 	= std::tan(kCircleTheta);
    static const float kCircleRadFactor 	= std::cos(kCircleTheta);

    // float v[kCircleSegmentsNum * 2];
    int v[kCircleSegmentsNum * 2];

	float cx = radius;
	float cy = 0.0f;
	unsigned vertexIdx = 0;

    auto x = pos.x();
    auto y = pos.y();

	for(unsigned i = 0; i < kCircleSegmentsNum; ++i, vertexIdx += 2)
	{
		// v[vertexIdx] = cx + x;
		// v[vertexIdx + 1] = cy + y;

		v[vertexIdx] = std::round(cx + x);
		v[vertexIdx + 1] = std::round(cy + y);


		float tx = -cy;
		float ty = cx;

		cx += tx * kCircleTanFactor;
		cy += ty * kCircleTanFactor;

		cx *= kCircleRadFactor;
		cy *= kCircleRadFactor;
	}

    setRenderColor(col);
    drawLines((const SDL_Point*)&v[0], kCircleSegmentsNum);
    

}

// template <std::size_t N>
// void Renderer::drawLines(const std::array<SDL_Point*, N>& points)
// {
//     drawLines(points.data(), point.size());
// }

void Renderer::setRenderColor(const Color c) const
{
    SDL_SetRenderDrawColor(_ren, c.R(), c.G(), c.B(), 255);
}

void Renderer::Present() const { SDL_RenderPresent(_ren); }

Texture* Renderer::AddTexture(texture_ptr texture)
{
    std::set<texture_ptr>::iterator ret;
    std::tie(ret, std::ignore) = _textures.insert(std::move(texture));
    return ret->get();
}
}
