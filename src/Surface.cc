#include "SDL2wrapper/include/Surface.h"

#include <vector>
#include <cassert>
#include <optional>
#include <utility>

#include "libs/SDL2/include/SDL_surface.h"
#include "libs/SDL2_image/include/SDL_image.h"

#include "SDL2wrapper/include/Exception.h"

namespace sdl2
{

Surface::Surface(SDL_Surface* surface) : surface_(surface)
{
    assert(surface_);
}

Surface::Surface(Uint32 flags, int width, int height, int depth,
        Uint32 Rm, Uint32 Gm, Uint32 Bm, Uint32 Am)
{
    surface_ = SurfaceSharedPtr(SDL_CreateRGBSurface(flags, width, height, depth, Rm, Gm, Bm, Am));
    if (surface_ == nullptr)
        throw SDLException("SDL_CreateRGBSurface");
}

Surface::Surface(void* pixels, int widht, int height, int depth, int pitch,
        Uint32 Rm, Uint32 Gm, Uint32 Bm, Uint32 Am)
{
    surface_ =  SurfaceSharedPtr(SDL_CreateRGBSurfaceFrom(pixels, widht, height, depth, pitch, Rm, Gm, Bm, Am));
    if (surface_ == nullptr)
        throw SDLException("SDL_CreateRGBSurfaceFrom");
}

#ifdef SDL2WRAPPER_IMAGE
Surface::Surface(const std::string& path)
{
    surface_ = SurfaceSharedPtr(IMG_Load(path.c_str()));
    if (surface_ == nullptr)
        throw SDLException("IMG_Load");
}
#endif

Surface::Surface(Surface&& other) noexcept :
    surface_(std::move(other.surface_))
{}

Surface& Surface::operator=(Surface&& other) noexcept
{
    if (&other == this)
        return *this;
    if (surface_ != nullptr)
        surface_ = std::move(other.surface_);
    return *this;
}

SDL_Surface* Surface::Get() const
{
    return surface_.get();
}

Surface Surface::Convert(const SDL_PixelFormat& format)
{
    SDL_Surface* surface = SDL_ConvertSurface(&*surface_, &format, 0);
    if (surface == nullptr)
        throw SDLException("SDL_ConvertSurface");
    return Surface(surface);
}

Surface Surface::Convert(Uint32 pixel_format)
{
    SDL_Surface* surface = SDL_ConvertSurfaceFormat(&*surface_, pixel_format, 0);
    if (surface == nullptr)
        throw SDLException("SDL_ConvertSurface");
    return Surface(surface);
}

void Surface::Blit(const std::optional<Rect>& srcrect, Surface& dst, const Rect& dstrect)
{
    SDL_Rect tmpdstrect = dstrect;
    SDL_Surface* dstsurface = &*(dst.Get());
    if (0 != SDL_BlitSurface(
            &*surface_, 
            srcrect == std::nullopt ? nullptr : &*srcrect,
            dstsurface, 
            &tmpdstrect
    ))
    {
        throw SDLException("SDL_BlitSurface");
    }
}

void Surface::BlitScaled(const std::optional<Rect>& srcrect, Surface& dst, const std::optional<Rect>& dstrect)
{
    SDL_Rect tmpdstrect;
    if (dstrect != std::nullopt)
        tmpdstrect = *dstrect;
    SDL_Surface* dstsurface = &*(dst.Get());
    if (0 != SDL_BlitScaled(
            &*surface_,
            srcrect == std::nullopt ? nullptr : &*srcrect,
            dstsurface,
            dstrect == std::nullopt ? nullptr : &tmpdstrect
    ))
    {
        throw SDLException("SDL_BlitScaled");
    }
}

Surface::LockHandle Surface::Lock()
{
    return LockHandle(*this);
}

Rect Surface::ClipRect() const
{
    SDL_Rect rect;
    SDL_GetClipRect(&*surface_, &rect);
    return rect;
}

Uint32 Surface::ColorKey() const
{
    Uint32 key;
    if (0 != SDL_GetColorKey(&*surface_, &key))
        throw SDLException("SDL_GetColorKey");
    return key;
}

Uint8 Surface::AlphaMod() const
{
    Uint8 alpha;
    if (0 != SDL_GetSurfaceAlphaMod(&*surface_, &alpha))
        throw SDLException("SDL_GetSurfaceAlphaMod");
    return alpha;
}

SDL_BlendMode Surface::BlendMode() const
{
    SDL_BlendMode blend;
    if (0 != SDL_GetSurfaceBlendMode(&*surface_, &blend))
        throw SDLException("SDL_GetSurfaceBlendMode");
    return blend;
}

Color Surface::ColorAndAlphaMod() const
{
    Color color;
    ColorMod(color.r, color.g, color.b);
    color.a = AlphaMod();
    return color;
}

void Surface::ColorMod(Uint8& r, Uint8& g, Uint8& b) const
{
    if (0 != SDL_GetSurfaceColorMod(&*surface_, &r, &g, &b))
        throw SDLException("SDL_GetSurfaceColorMod");
}

Surface& Surface::ClipRect(const std::optional<Rect>& rect)
{
    if (SDL_TRUE != SDL_SetClipRect(
        &*surface_,
        rect == std::nullopt ? nullptr : &*rect
    ))
    {
        throw SDLException("SDL_SetClipRect");
    }
    return *this;
}

Surface& Surface::ColorKey(bool flag, Uint32 key)
{
    if (0 != SDL_SetColorKey(&*surface_, flag, key))
        throw SDLException("SDL_SetColorKey");
    return *this;
}

Surface& Surface::AlphaMod(Uint8 alpha)
{
    if (0 != SDL_SetSurfaceAlphaMod(&*surface_, alpha))
        throw SDLException("SDL_SetSurfaceAlphaMod");
    return *this;
}

Surface& Surface::BlendMode(SDL_BlendMode blendMode)
{
    if (0 != SDL_SetSurfaceBlendMode(&*surface_, blendMode))
        throw SDLException("SDL_SetSurfaceBlendMode");
    return *this;
}

Surface& Surface::ColorMod(Uint8 r, Uint8 g, Uint8 b)
{
    if (0 != SDL_SetSurfaceColorMod(&*surface_, r, g, b))
        throw SDLException("SDL_SetSurfaceColorMod");
    return *this;
}

Surface& Surface::ColorAndAlphaMod(const Color& color)
{
    return ColorMod(color.r, color.g, color.b).AlphaMod(color.a);
}

Surface& Surface::RLE(bool flag)
{
    if (SDL_SetSurfaceRLE(&*surface_, flag ? 1 : 0) != 0)
        throw SDLException("SDL_SetSurfaceRLE");
    return *this;
}

Surface& Surface::FillRect(const std::optional<Rect>& rect, Uint32 color)
{
    if (0 != SDL_FillRect(
        &*surface_,
        rect == std::nullopt ? nullptr : &*rect,
        color
    ))
        throw SDLException("SDL_FillRect");
    return *this;
}

Surface& Surface::FillRects(const Rect* rects, int count, Uint32 color)
{
    std::vector<SDL_Rect> sdl_rects;
    sdl_rects.reserve(static_cast<size_t>(count));
    for (const Rect* r = rects; r != rects + count; ++r)
        sdl_rects.emplace_back(*r);

    if (0 != SDL_FillRects(&*surface_, sdl_rects.data(), count, color))
        throw SDLException("SDL_FillRects");
    return *this;
}

Point Surface::Size() const
{
    return Point(surface_->w, surface_->h);
}

int Surface::Width() const
{
    return surface_->w;
}

int Surface::Height() const
{
    return surface_->h;
}

Uint32 Surface::Format() const
{
    return surface_->format->format;
}

} // sdl2
