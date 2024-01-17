#ifndef SDL2WRAPPER_SDLTTF_H_
#define SDL2WRAPPER_SDLTTF_H_

namespace sdl2
{

class SDLTTF
{

public:
    SDLTTF();
    virtual ~SDLTTF();

    SDLTTF(const SDLTTF& other) = delete;
    SDLTTF& operator=(const SDLTTF& other) = delete;

    SDLTTF(SDLTTF& other) = delete;
    SDLTTF& operator=(SDLTTF& other) = delete;
};

}

#endif