#ifndef SDL2WRAPPER_IMAGE_H_
#define SDL2WRAPPER_IMAGE_H_

namespace sdl2
{

class SDLImage
{
public:
    explicit SDLImage(int flags=0);
    virtual ~SDLImage();

    int Formats(int flags);
    int Formats();

    SDLImage(const SDLImage& other) = delete;
    SDLImage& operator=(const SDLImage& other) = delete;

    SDLImage(SDLImage&& other) = delete;
    SDLImage& operator=(SDLImage&& other) = delete;
};

}

#endif