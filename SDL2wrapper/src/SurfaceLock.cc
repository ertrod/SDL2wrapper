#include "SDL2wrapper/include/Surface.h"

#include <utility>

#include "libs/SDL2/include/SDL_surface.h"

#include "SDL2wrapper/include/Exception.h"

namespace sdl2
{

Surface::LockHandle::LockHandle() : surface_(nullptr)
{}

Surface::LockHandle::LockHandle(Surface& surface)
{
    SDL_Surface* surf = surface.Get();
    if (SDL_MUSTLOCK(surf))
        if (SDL_LockSurface(surf))
            throw SDLException("SDL_LockSurface");
}

Surface::LockHandle::LockHandle(Surface::LockHandle&& other) noexcept :
    surface_(std::move(other.surface_))
{}

Surface::LockHandle& Surface::LockHandle::operator=(Surface::LockHandle&& other) noexcept
{
    if (&other == this)
        return *this;
    if (surface_ != nullptr)
    {
        if (SDL_MUSTLOCK(surface_.get()))
            SDL_UnlockSurface(surface_.get());
    }

    surface_ = std::move(other.surface_);
    return *this;
}

Surface::LockHandle::~LockHandle()
{
    if (surface_ != nullptr)
        if (SDL_MUSTLOCK(surface_.get()))
            SDL_UnlockSurface(surface_.get());
}

void* Surface::LockHandle::Pixels() const 
{
    return surface_.get()->pixels;
}

int Surface::LockHandle::Pitch() const
{
    return surface_.get()->pitch;
}

const SDL_PixelFormat& Surface::LockHandle::Format() const
{
    return *(surface_.get()->format);
}

} // sdl2