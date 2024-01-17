#include "SDL2wrapper/include/Texture.h"

#include <cassert>
#include <utility>


#include "SDL2wrapper/include/Pointers.h"
#include "SDL2wrapper/include/Rect.h"
#include "SDL2wrapper/include/Exception.h"
#include "SDL2wrapper/include/Surface.h"

namespace sdl2
{

Texture::Texture(SDL_Texture* texture) : texture_(texture)
{
    assert(texture);
}

Texture::Texture(Texture&& other) noexcept 
    : texture_(std::move(other.texture_))
{}

Texture& Texture::operator=(Texture&& other) noexcept
{
    if (&other == this)
        return *this;
    if (texture_ != nullptr)
        SDL_DestroyTexture(texture_.get());

    texture_ = std::move(other.texture_);

    return *this;
}

SDL_Texture* Texture::Get() const
{
    return texture_.get();
}

Texture& Texture::Update(const std::optional<Rect>& rect, const void* pixels, int pitch)
{
    if (0 != SDL_UpdateTexture(
        texture_.get(),
        rect == std::nullopt ? nullptr : &*rect,
        pixels, pitch
    ))
    {
        throw SDLException("SDL_UpdateTexture");
    }

    return *this;
}

Texture& Texture::Update(const std::optional<Rect>& rect, Surface& surface)
{
    Rect real_rect = rect == std::nullopt ? Rect(0, 0, Width(), Height()) : *rect;

    real_rect.w = std::min(real_rect.w, surface.Width());
    real_rect.h = std::min(real_rect.h, surface.Height());

    if (Format() == surface.Format())
    {
        Surface::LockHandle lock = surface.Lock();
        return Update(real_rect, lock.Pixels(), lock.Pitch());
    }
    else
    {
        Surface converted = surface.Convert(Format());
        Surface::LockHandle lock = converted.Lock();

        return Update(real_rect, lock.Pixels(), lock.Pitch());
    }
}

Texture& Texture::Update(const std::optional<Rect>& rect, Surface&& surface)
{
    Rect real_rect = (rect == std::nullopt) ? Rect(0, 0, Width(), Height()) : *rect;

    real_rect.w = std::min(real_rect.w, surface.Width());
    real_rect.h = std::min(real_rect.h, surface.Height());

    if (Format() == surface.Format())
    {
        Surface::LockHandle lock = surface.Lock();
        return Update(real_rect, lock.Pixels(), lock.Pitch());
    }
    else
    {
        Surface converted = surface.Convert(Format());
        Surface::LockHandle lock = converted.Lock();
      
        void* p = lock.Pixels();
        int i = lock.Pitch();

        return Update(real_rect, lock.Pixels(), lock.Pitch());
    }
}

Texture& Texture::UpdateYUV(
    const std::optional<Rect>& rect,
    const Uint8* yplane, int ypitch,
    const Uint8* uplane, int upitch,
    const Uint8* vplane, int vpitch
    )
{
    if (0 != SDL_UpdateYUVTexture(
        texture_.get(),
        rect == std::nullopt ? nullptr : &*rect,
        yplane, ypitch,
        uplane, upitch,
        vplane, vpitch
    ))
    {
        throw SDLException("SDL_UpdateYUVTexture");
    }
    return *this;
}

Texture& Texture::BlendMode(SDL_BlendMode blendMode)
{
    if (0 != SDL_SetTextureBlendMode(texture_.get(), blendMode))
    {
        throw SDLException("SDL_SetTextureBlendMode");
    }
    return *this;
}

Texture& Texture::AlphaMod(Uint8 alpha)
{
    if (0 != SDL_SetTextureAlphaMod(texture_.get(), alpha))
    {
        throw SDLException("SDL_SetTextureAlphaMod");
    }
    return *this;
}

Texture& Texture::SetColorMod(Uint8 r, Uint8 g, Uint8 b)
{
    if (0 != SDL_SetTextureColorMod(texture_.get(), r, g, b))
    {
        throw SDLException("SDL_SetTextureColorMod");
    }
    return *this;
}

Texture& Texture::ColorAndAlphaMod(const Color& color)
{
    return SetColorMod(color.r, color.g, color.b).AlphaMod(color.a);
}

Texture::LockHandle Texture::Lock(const std::optional<Rect>& rect)
{
    return LockHandle(this, rect);
}

Uint32 Texture::Format() const
{
    Uint32 format;
    if (0 != SDL_QueryTexture(texture_.get(), &format, nullptr, nullptr, nullptr))
    {
        throw SDLException("SDL_QueryTexture");
    }
    return format;
}

int Texture::Access() const 
{
    int access;
    if (0 != SDL_QueryTexture(texture_.get(), nullptr, &access, nullptr, nullptr))
    {
        throw SDLException("SDL_QueryTexture");
    }
    return access;
}

int Texture::Width() const
{
    int width;
    if (0 != SDL_QueryTexture(texture_.get(), nullptr, nullptr, &width, nullptr))
    {
        throw SDLException("SDL_QueryTexture");
    }
    return width;
}

int Texture::Height() const
{
    int height;
    if (0 != SDL_QueryTexture(texture_.get(), nullptr, nullptr, nullptr, &height))
    {
        throw SDLException("SDL_QueryTexture");
    }
    return height;
}

Point Texture::Size() const
{
    int w, h;
    if (0 != SDL_QueryTexture(texture_.get(), nullptr, nullptr, &w, &h))
    {
        throw SDLException("SDL_QueryTexture");
    }
    return Point(w, h);
}

Uint8 Texture::AlphaMod() const
{
    Uint8 alpha;
    if (0 != SDL_GetTextureAlphaMod(texture_.get(), &alpha))
    {
        throw SDLException("SDL_GetTextureAlphaMod");
    }
    return alpha;
}

SDL_BlendMode Texture::BlendMode() const
{
    SDL_BlendMode blend;
    if (0 != SDL_GetTextureBlendMode(texture_.get(), &blend))
    {
        throw SDLException("SDL_GetTextureBlendMode");
    }
    return blend;
}

void Texture::GetColorMod(Uint8& r, Uint8& g, Uint8& b)
{
    if (0 != SDL_GetTextureColorMod(texture_.get(), &r, &g, &b))
    {
        throw SDLException("SDL_GetTextureColorMod");
    }
}

Color Texture::ColorAndAlphaMod() 
{
    Color color;
    GetColorMod(color.r, color.g, color.b);
    color.a = AlphaMod();
    return color;
}

} //sdl2
