#include "SDL2wrapper/include/Exception.h"

#include <string>
#include <sstream>

#include "libs/SDL2/include/SDL_error.h"

namespace sdl2
{

std::string SDLException::make(const char* function, const char* sdl_error)
{
    std::string tmp(function);
    tmp += " failed: ";
    tmp += sdl_error;
    return tmp;
}

SDLException::SDLException(const char* function):
    std::runtime_error(make(function, SDL_GetError())),
    sdl_function_(function),
    sdl_error_(SDL_GetError())
{}

SDLException::~SDLException() noexcept
{}

std::string SDLException::SDLFunction() const
{
    return sdl_function_;
}

std::string SDLException::SDLError() const
{
    return sdl_error_;
}


}
