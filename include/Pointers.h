#ifndef SDL2WRAPPER_POINTERS_H_
#define SDL2WRAPPER_POINTERS_H_

#include <memory>

#include "libs/SDL2/include/SDL.h"

namespace sdl2
{

struct SDL_Deleter
{
    void operator()(SDL_Surface* ptr) 
    {
        if (ptr)
            SDL_FreeSurface(ptr);
    }
    void operator()(SDL_Texture* ptr)
    {
        if (ptr)
            SDL_DestroyTexture(ptr);
    }
    void operator()(SDL_Renderer* ptr)
    {
        if (ptr)
            SDL_DestroyRenderer(ptr);
    }
    void operator()(SDL_Window* ptr)
    {
        if (ptr)
            SDL_DestroyWindow(ptr);
    }
    void operator()(SDL_RWops* ptr)
    {
        if (ptr)
            SDL_RWclose(ptr);
    }
};

using SurfacePtr = std::unique_ptr<SDL_Surface, SDL_Deleter>;
using TexturePtr = std::unique_ptr<SDL_Texture, SDL_Deleter>;
using RendererPtr = std::unique_ptr<SDL_Renderer, SDL_Deleter>;
using WindowPtr = std::unique_ptr<SDL_Window, SDL_Deleter>;
using RWopsPtr = std::unique_ptr<SDL_RWops, SDL_Deleter>;

template<class T, class D = std::default_delete<T>>
struct SharedPtrWithDeleter : public std::shared_ptr<T>
{
    explicit SharedPtrWithDeleter(T* t = nullptr)
        : std::shared_ptr<T>(t, D()) {}
    void reset(T* t = nullptr)
    {
        std::shared_ptr<T>::reset(t, D());
    }
};

using SurfaceSharedPtr = SharedPtrWithDeleter<SDL_Surface, SDL_Deleter>;
using TextureSharedPtr = SharedPtrWithDeleter<SDL_Texture, SDL_Deleter>;
using RendererSharedPtr = SharedPtrWithDeleter<SDL_Renderer, SDL_Deleter>;
using WindowSharedPtr = SharedPtrWithDeleter<SDL_Window, SDL_Deleter>;
using RWopsSharedPtr = SharedPtrWithDeleter<SDL_RWops, SDL_Deleter>;

} // sdl2

#endif