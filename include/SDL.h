#ifndef SDL2WRAPPER_SDL_H_
#define SDL2WRAPPER_SDL_H_

#include "SDL/SDL2/include/SDL_stdinc.h"

namespace sdl2
{

class SDL
{
public:
    SDL(Uint32 flags);
    virtual ~SDL();

    SDL(const SDL& other) = delete;
    SDL& operator=(const SDL& other) = delete;
    
    SDL(SDL&& other) = delete;
    SDL& operator=(SDL&& other) = delete;

    Uint32 IsInitialized(Uint32 flags);
    void InitSub(Uint32 flags);
    void CloseSub(Uint32 flags);
};

} // sdl2

#endif