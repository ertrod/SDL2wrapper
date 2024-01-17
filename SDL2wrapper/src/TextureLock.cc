#include "SDL2wrapper/include/Texture.h"

#include "SDL2/include/SDL_render.h"

#include "SDL2wrapper/include/Rect.h"
#include "SDL2wrapper/include/Exception.h"

namespace sdl2
{

Texture::LockHandle::LockHandle(): 
    texture_(nullptr), pixels_(nullptr), pitch_(0)
{}

Texture::LockHandle::LockHandle(Texture* texture, const std::optional<Rect>& rect):
    texture_(texture)
{
    if (0 != SDL_LockTexture(
        texture_->Get(), 
        rect == std::nullopt ? nullptr : &*rect,
        &pixels_, &pitch_
    ))
    {
        throw SDLException("SDL_LockTexture");
    }
}

Texture::LockHandle::LockHandle(Texture::LockHandle&& other) noexcept 
    : texture_(other.texture_), pixels_(other.pixels_), pitch_(other.pitch_)
{
    other.texture_ = nullptr;
    other.pixels_ = nullptr;
    other.pitch_ = 0;
}

Texture::LockHandle& Texture::LockHandle::operator=(Texture::LockHandle&& other) noexcept
{
    if (&other == this)
        return *this;
    if (texture_ != nullptr)
        SDL_UnlockTexture(texture_->Get());
    
    texture_ = other.texture_;
    pixels_ = other.pixels_;
    pitch_ = other.pitch_;


    other.texture_ = nullptr;
    other.pixels_ = nullptr;
    other.pitch_ = 0;
    
    return *this;
}

Texture::LockHandle::~LockHandle()
{
    if (texture_ != nullptr)
        SDL_UnlockTexture(texture_->Get());
}

void* Texture::LockHandle::Pixels() const
{
    return pixels_;
}

int Texture::LockHandle::Pitch() const
{
    return pitch_;
}

} // sdl2