#include "SDL2wrapper/include/Renderer.h"

#include <optional>
#include <vector>
#include <cassert>
#include <utility>

#include "SDL2/include/SDL_stdinc.h"
#include "SDL2/include/SDL_blendmode.h"

#ifdef SDL2WRAPPER_IMAGE
#include "SDL2_image/include/SDL_image.h"
#endif

#include "SDL2wrapper/include/Pointers.h"
#include "SDL2wrapper/include/Point.h"
#include "SDL2wrapper/include/Color.h"
#include "SDL2wrapper/include/Exception.h"
#include "SDL2wrapper/include/Rect.h"
#include "SDL2wrapper/include/Window.h"
#include "SDL2wrapper/include/Surface.h"
#include "SDL2wrapper/include/Texture.h"

namespace sdl2
{

Renderer::Renderer(SDL_Renderer* renderer) : renderer_(renderer)
{
    assert(renderer);
}

Renderer::Renderer(Window& window, int index, Uint32 flags)
{
    renderer_ = RendererPtr(SDL_CreateRenderer(window.Get(), index, flags));
    if (renderer_ == nullptr)
    {
        throw SDLException("SDL_CreateRenderer");
    }
}

Renderer::Renderer(Renderer&& other) noexcept
    : renderer_(std::move(other.renderer_))
{}

Renderer& Renderer::operator=(Renderer&& other) noexcept
{
    if (&other == this)
        return *this;
    if (renderer_ != nullptr)
        SDL_DestroyRenderer(renderer_.get());
    renderer_ = std::move(other.renderer_);
    return *this;
}

SDL_Renderer* Renderer::Get() const
{
    return renderer_.get();
}

Renderer& Renderer::Present()
{
    SDL_RenderPresent(renderer_.get());
    return *this;
}

Renderer& Renderer::Clear()
{
    if (0 != SDL_RenderClear(renderer_.get()))
    {
        throw SDLException("SDL_RenderClear");
    }
    return *this;
}

void Renderer::GetInfo(SDL_RendererInfo& info)
{
    if (0 != SDL_GetRendererInfo(renderer_.get(), &info))
    {
        throw SDLException("SDL_RendererInfo");
    }
}

Renderer& Renderer::Copy(Texture& texture, const std::optional<Rect>& srcrect, const std::optional<Rect>& dstrect)
{
    int result = SDL_RenderCopy(renderer_.get(), texture.Get(), 
        srcrect == std::nullopt ? nullptr : &*srcrect,
        dstrect == std::nullopt ? nullptr : &*dstrect
    );
    if (result != 0)
    {
        throw SDLException("SDL_RenderCopy");
    }
    return *this;
}

Renderer& Renderer::Copy(Texture& texture, const std::optional<Rect>& srcrect, const Point& dstpoint)
{
    Rect dstrect(
        dstpoint.x, dstpoint.y, 
        srcrect == std::nullopt ? texture.Width() : srcrect->w,
        srcrect == std::nullopt ? texture.Height(): srcrect->h
    );
    return Copy(texture, srcrect, dstrect);
}
Renderer& Renderer::Copy(Texture& texture, const std::optional<Rect>& srcrect, const std::optional<Rect>& dstrect, double angle, const std::optional<Point>& center, int flip)
{
    int result = SDL_RenderCopyEx(renderer_.get(), texture.Get(),
        srcrect == std::nullopt ? nullptr : &*srcrect,
        dstrect == std::nullopt ? nullptr : &*dstrect,
        angle,
        center == std::nullopt ? nullptr : &*center, 
        static_cast<SDL_RendererFlip>(flip)
    );
    if (result != 0)
    {
        throw SDLException("SDL_RenderCopyEx");
    }
    return *this;
}

Renderer& Renderer::Copy(Texture& texture, const std::optional<Rect>& srcrect, const Point& dstpoint, double angle, const std::optional<Point>& center, int flip)
{
    Rect dstrect(
        dstpoint.x, dstpoint.y,
        srcrect == std::nullopt ? texture.Width() : srcrect->w,
        srcrect == std::nullopt ? texture.Height() : srcrect->h
    );
    return Copy(texture, srcrect, dstrect, angle, center, flip);
}

Renderer& Renderer::FillCopy(Texture& texture, const std::optional<Rect>& srcrect, const std::optional<Rect>& dstrect, const Point& offset, int flip)
{
    Rect src = srcrect == std::nullopt ? Rect(0, 0, texture.Width(), texture.Height()) : *srcrect;
    Rect dst = dstrect == std::nullopt ? Rect(0, 0, OutputWidth(), OutputHeight()) : *dstrect;

    Rect start_tile(
        offset.x,
        offset.y,
        src.w,
        src.h
    );

    if (start_tile.x + start_tile.w <= 0)
        start_tile.x += (-start_tile.x) / start_tile.w * start_tile.w;
    if (start_tile.x > 0)
        start_tile.x -= (start_tile.x + start_tile.w - 1) / start_tile.w * start_tile.w;

    if (start_tile.y + start_tile.h <= 0)
        start_tile.y += (-start_tile.y) / start_tile.h * start_tile.h;
    if (start_tile.y > 0)
        start_tile.y -= (start_tile.y + start_tile.h - 1) / start_tile.h * start_tile.h;

    for (int y = start_tile.y; y < dst.h; y += start_tile.h) 
    {
        for (int x = start_tile.x; x < dst.w; x += start_tile.w) 
        {
            Rect tile_src = src;
            Rect tile_dst(x, y, start_tile.w, start_tile.h);

            // clamp with dstrect
            int xunderflow = -x;
            if (xunderflow > 0) {
                tile_src.w -= xunderflow;
                tile_src.x += xunderflow;
                tile_dst.w -= xunderflow;
                tile_dst.x += xunderflow;
            }

            int yunderflow = -y;
            if (yunderflow > 0) {
                tile_src.h -= yunderflow;
                tile_src.y += yunderflow;
                tile_dst.h -= yunderflow;
                tile_dst.y += yunderflow;
            }

            int xoverflow = tile_dst.x + tile_dst.w - dst.w;
            if (xoverflow > 0) {
                tile_src.w -= xoverflow;
                tile_dst.w -= xoverflow;
            }

            int yoverflow = tile_dst.y + tile_dst.h - dst.h;
            if (yoverflow > 0) {
                tile_src.h -= yoverflow;
                tile_dst.h -= yoverflow;
            }

            // make tile_dst absolute
            tile_dst.x += dst.x;
            tile_dst.y += dst.y;

            if (flip != 0) {
                // mirror tile_src inside src to take flipping into account
                if (flip & SDL_FLIP_HORIZONTAL)
                    tile_src.x = src.w - tile_src.x - tile_src.w;

                if (flip & SDL_FLIP_VERTICAL)
                    tile_src.y = src.h - tile_src.y - tile_src.h;

                Copy(texture, tile_src, tile_dst, 0.0, std::nullopt, flip);
            } else {
                Copy(texture, tile_src, tile_dst);
            }
        }
    }
    return *this;
}

Renderer& Renderer::SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    if (0 != SDL_SetRenderDrawColor(renderer_.get(), r, g, b, a))
    {
        throw SDLException("SDL_SetRenderDrawColor");
    }
    return *this;
}

Renderer& Renderer::SetDrawColor(const Color& color)
{
    return SetDrawColor(color.r, color.g, color.b, color.a);
}

Renderer& Renderer::Target()
{
    if (SDL_SetRenderTarget(renderer_.get(), nullptr) != 0)
    {
        throw SDLException("SDL_SetRenderTarget");
    }
    return *this;
}

Renderer& Renderer::Target(Texture& texture)
{
    if (SDL_SetRenderTarget(renderer_.get(), texture.Get()) != 0)
    {
        throw SDLException("SDL_SetRenderTarget");
    }
    return *this;
}

Renderer& Renderer::DrawBlendMode(SDL_BlendMode blend)
{
    if (0 != SDL_SetRenderDrawBlendMode(renderer_.get(), blend))
    {
        throw SDLException("SDL_SetRenderDrawBlendMode");
    }
    return *this;
}

Renderer& Renderer::DrawPoint(int x, int y)
{
    if (0 != SDL_RenderDrawPoint(renderer_.get(), x, y))
    {
        throw SDLException("SDL_RenderDrawPoint");
    }
    return *this;
}

Renderer& Renderer::DrawPoint(const Point& p)
{
    return DrawPoint(p.x, p.y);
}

Renderer& Renderer::DrawPoints(const Point* points, int count)
{
    std::vector<SDL_Point> sdl_points;
    sdl_points.reserve(static_cast<size_t>(count));
    for (const Point* p = points; p != points + count; p++)
        sdl_points.emplace_back(*p);
    
    if (0 != SDL_RenderDrawPoints(renderer_.get(), sdl_points.data(), count))
    {
        throw SDLException("SDL_RenderDrawPoints");
    }
    return *this;
}

Renderer& Renderer::DrawLine(int x1, int y1, int x2, int y2)
{
    if (0 != SDL_RenderDrawLine(renderer_.get(), x1, y1, x2, y2))
    {
        throw SDLException("SDL_RenderDrawLine");
    }
    return *this;
}

Renderer& Renderer::DrawLine(const Point& start, const Point& end)
{
    return DrawLine(start.x, start.y, end.x, end.y);
}

Renderer& Renderer::DrawLines(const Point* points, int count)
{
    std::vector<SDL_Point> sdl_points;
    sdl_points.reserve(static_cast<size_t>(count));
    for (const Point* p = points; p != points + count; p++)
        sdl_points.emplace_back(*p);
    
    if (0 != SDL_RenderDrawLines(renderer_.get(), sdl_points.data(), count))
    {
        throw SDLException("SDL_RenderDrawLines");
    }
    return *this;
}

Renderer& Renderer::DrawRect(int x1, int y1, int x2, int y2)
{
    SDL_Rect rect = {x1, y1, x2 - x1+1, y2 - y1+1};
    if (0 != SDL_RenderDrawRect(renderer_.get(), &rect))
    {
        throw SDLException("SDL_RenderDrawRect");
    }
    return *this;
}

Renderer& Renderer::DrawRect(const Point& start, const Point& end)
{
    return DrawRect(start.x, start.y, end.x, end.y);
}

Renderer& Renderer::DrawRect(const Rect& r)
{
    if (0 != SDL_RenderDrawRect(renderer_.get(), &r))
    {
        throw SDLException("SDL_RenderDrawRect");
    }
    return *this;
}

Renderer& Renderer::DrawRects(const Rect* rects, int count)
{
    std::vector<SDL_Rect> sdl_rects;
    sdl_rects.reserve(static_cast<size_t>(count));
    for (const Rect* r = rects; r != rects + count; r++)
        sdl_rects.emplace_back(*r);

    if (0 != SDL_RenderDrawRects(renderer_.get(), sdl_rects.data(), count))
    {
        throw SDLException("SDL_RenderDrawRects");
    }
    return *this;
}


Renderer& Renderer::FillRect(int x1, int y1, int x2, int y2)
{
    SDL_Rect rect = {x1, y1, x2 - x1+1, y2 - y1+1};
    if (0 != SDL_RenderFillRect(renderer_.get(), &rect))
    {
        throw SDLException("SDL_RenderDrawRect");
    }
    return *this;
}

Renderer& Renderer::FillRect(const Point& start, const Point& end)
{
    return FillRect(start.x, start.y, end.x, end.y);
}

Renderer& Renderer::FillRect(const Rect& r)
{
    if (0 != SDL_RenderFillRect(renderer_.get(), &r))
    {
        throw SDLException("SDL_RenderDrawRect");
    }
    return *this;
}

Renderer& Renderer::FillRects(const Rect* rects, int count)
{
    std::vector<SDL_Rect> sdl_rects;
    sdl_rects.reserve(static_cast<size_t>(count));
    for (const Rect* r = rects; r != rects + count; r++)
        sdl_rects.emplace_back(*r);

    if (0 != SDL_RenderFillRects(renderer_.get(), sdl_rects.data(), count))
    {
        throw SDLException("SDL_RenderDrawRects");
    }
    return *this;
}

void Renderer::ReadPixels(const std::optional<Rect>& rect, Uint32 format, void* pixels, int pitch)
{
    if (0 != SDL_RenderReadPixels(renderer_.get(),
        rect == std::nullopt ? nullptr : &*rect,
        format, pixels, pitch
    ))
    {
        throw SDLException("SDL_RenderReadPixels");
    }
}

Renderer& Renderer::ClipRect(const std::optional<Rect>& rect)
{
    if (0 != SDL_RenderSetClipRect(renderer_.get(), 
        rect == std::nullopt ? nullptr : &* rect
    ))
    {
        throw SDLException("SDL_RenderSetClipRect");
    }
    return *this;
}

Renderer& Renderer::LogicalSize(int w, int h)
{
    if (0 != SDL_RenderSetLogicalSize(renderer_.get(), w, h))
    {
        throw SDLException("SDL_RenderSetLogicalSize");
    }
    return *this;
}

Renderer& Renderer::Scale(float scaleX, float scaleY)
{
    if (0 != SDL_RenderSetScale(renderer_.get(), scaleX, scaleY))
    {
        throw SDLException("SDL_RenderSetScale");
    }
    return *this;
}

Renderer& Renderer::Viewport(const std::optional<Rect>& rect)
{
    if (0 != SDL_RenderSetViewport(renderer_.get(), 
        rect == std::nullopt ? nullptr : &*rect
    ))
    {
        throw SDLException("SDL_RenderSetViewport");
    }
    return *this;
}

bool Renderer::TargetSupported() const
{
    return SDL_RenderTargetSupported(renderer_.get()) == SDL_TRUE;
}

std::optional<Rect> Renderer::ClipRect() const
{
    SDL_Rect rect;
    SDL_RenderGetClipRect(renderer_.get(), &rect);

    if (SDL_RectEmpty(&rect))
        return std::nullopt;
    
    return Rect(rect);
}

Point Renderer::LogicalSize() const
{
    int w, h;
    SDL_RenderGetLogicalSize(renderer_.get(), &w, &h);
    return Point(w, h);
}

int Renderer::LogicalWidth() const
{
    int w;
    SDL_RenderGetLogicalSize(renderer_.get(), &w, nullptr);
    return w;
}

int Renderer::LogicalHeight() const
{
    int h;
    SDL_RenderGetLogicalSize(renderer_.get(), nullptr, &h);
    return h;
}

void Renderer::Scale(float* scaleX, float* scaleY)
{
    SDL_RenderGetScale(renderer_.get(), scaleX, scaleY);
}

float Renderer::XScale() const
{
    float scalex;
    SDL_RenderGetScale(renderer_.get(), &scalex, nullptr);
    return scalex;
}

float Renderer::YScale() const
{
    float scaley;
    SDL_RenderGetScale(renderer_.get(), &scaley, nullptr);
    return scaley;
}

Rect Renderer::Viewport() const
{
    SDL_Rect rect;
    SDL_RenderGetViewport(renderer_.get(), &rect);
    return Rect(rect);
}

SDL_BlendMode Renderer::BlendMode() const
{
    SDL_BlendMode blend;
    if (0 != SDL_GetRenderDrawBlendMode(renderer_.get(), &blend))
    {
        throw SDLException("SDL_GetRenderDrawBlendMode");
    }
    return blend;
}

Color Renderer::GetDrawColor()
{
    Color color;
    GetDrawColor(color.r, color.g, color.b, color.a);
    return color;
}

void Renderer::GetDrawColor(Uint8& r, Uint8& g, Uint8& b, Uint8& a)
{
    if (0 != SDL_GetRenderDrawColor(renderer_.get(), &r, &g, &b, &a))
    {
        throw SDLException("SDL_GetRenderDrawColor");
    }
}

Point Renderer::OutputSize() const
{
    int w, h;
    if (0 != SDL_GetRendererOutputSize(renderer_.get(), &w, &h))
    {
        throw SDLException("SDL_GetRendererOutputSize");
    }
    return Point(w, h);
}

int Renderer::OutputWidth() const
{
    int w;
    if (0 != SDL_GetRendererOutputSize(renderer_.get(), &w, nullptr))
    {
        throw SDLException("SDL_GetRendererOutputSize");
    }
    return w;
}

int Renderer::OutputHeight() const
{
    int h;
    if (0 != SDL_GetRendererOutputSize(renderer_.get(), nullptr, &h))
    {
        throw SDLException("SDL_GetRendererOutputSize");
    }
    return h;
}

Texture CreateTexture(Renderer& renderer, Uint32 format, int access, int w, int h)
{
    SDL_Texture* texture = SDL_CreateTexture(renderer.Get(), format, access, w, h);
    if (texture == nullptr)
    {
        throw SDLException("SDL_CreateTexture");
    }
    return Texture(texture);
}

#ifdef SDL2WRAPPER_IMAGE
Texture CreateTexture(Renderer& renderer, const std::string& filename)
{
    SDL_Texture* texture = IMG_LoadTexture(renderer.Get(), filename.c_str());
    if (texture == nullptr)
    {
        throw SDLException("IMG_LoadTexture");
    }
    return Texture(texture);
}
#endif

Texture CreateTexture(Renderer& renderer, const Surface& surface)
{
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer.Get(), surface.Get());
    if (texture == nullptr)
    {
        throw SDLException("SDL_CreateTextureFromSurface");
    }
    return Texture(texture);
}

} // sdl2