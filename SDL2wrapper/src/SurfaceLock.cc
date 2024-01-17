#include "SDL2wrapper/include/Surface.h"

#include <utility>

#include "SDL2/include/SDL_surface.h"

#include "SDL2wrapper/include/Exception.h"

namespace sdl2
{

Surface::LockHandle::LockHandle() : surface_(nullptr) {
}

Surface::LockHandle::LockHandle(Surface* surface) : surface_(surface) {
    if (SDL_MUSTLOCK(surface_->Get())) {
        if (SDL_LockSurface(surface_->Get()))
            throw SDLException("SDL_LockSurface");
    }
}

Surface::LockHandle::LockHandle(Surface::LockHandle&& other) noexcept 
    : surface_(std::move(other.surface_)) 
{
}

Surface::LockHandle& Surface::LockHandle::operator=(Surface::LockHandle&& other) noexcept {
    if (&other == this)
        return *this;

    if (surface_ != nullptr) {
        if (SDL_MUSTLOCK(surface_->Get()))
            SDL_UnlockSurface(surface_->Get());
    }

    surface_ = std::move(other.surface_);

    return *this;
    }

Surface::LockHandle::~LockHandle() {
    if (surface_ != nullptr) {
        if (SDL_MUSTLOCK(surface_->Get()))
            SDL_UnlockSurface(surface_->Get());
    }
}

void* Surface::LockHandle::Pixels() const {
    return surface_->Get()->pixels;
}

int Surface::LockHandle::Pitch() const {
    return surface_->Get()->pitch;
}

const SDL_PixelFormat& Surface::LockHandle::Format() const {
    return *surface_->Get()->format;
}


} // sdl2