#include "SDL2wrapper/include/SDL.h"

#include "SDL/SDL2/include/SDL.h"

#include "SDL2wrapper/include/Exception.h"


namespace sdl2
{

SDL::SDL(Uint32 flags)
{
    if (SDL_Init(flags) != 0)
    {
        throw SDLException("SDL_Init");
    }
}

SDL::~SDL()
{
    SDL_Quit();
}

Uint32 SDL::IsInitialized(Uint32 flags)
{
    return SDL_WasInit(flags);
}

void SDL::InitSub(Uint32 flags)
{
    if (SDL_InitSubSystem(flags) != 0)
    {
        SDLException("SDL_InitSubSystem");
    }
}

void SDL::CloseSub(Uint32 flags)
{
    SDL_QuitSubSystem(flags);
}

}