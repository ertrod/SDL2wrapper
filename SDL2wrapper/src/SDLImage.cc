#include "SDL2wrapper/include/SDLImage.h"

#include "SDL2_image/include/SDL_image.h"

#include "SDL2wrapper/include/Exception.h"

namespace sdl2
{

SDLImage::SDLImage(int flags)
{
    if (flags != IMG_Init(flags) & flags)
        throw SDLException("IMG_Init");
}

SDLImage::~SDLImage()
{
    IMG_Quit();
}

int SDLImage::Formats(int flags)
{
    int ret;
    if (flags != (ret = IMG_Init(flags) & flags))
        throw SDLException("IMG_Init");
    return ret;
}

int SDLImage::Formats()
{
    return IMG_Init(0);
}

} // sdl2
