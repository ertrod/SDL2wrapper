#include "SDL2wrapper/include/SDLTTF.h"

#include "SDL2_ttf/include/SDL_ttf.h"

#include "SDL2wrapper/include/Exception.h"

namespace sdl2
{

SDLTTF::SDLTTF()
{
    if (TTF_Init() != 0)
        throw SDLException("TTF_Init()");
}

SDLTTF::~SDLTTF()
{
    TTF_Quit();
}

}