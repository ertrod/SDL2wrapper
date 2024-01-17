#ifndef SDL2WRAPPER_COLOR_H_
#define SDL2WRAPPER_COLOR_H_

#include <iostream>

#include "SDL/SDL2/include/SDL_pixels.h"

namespace sdl2
{

class Color : public SDL_Color
{
public:
    constexpr Color(): SDL_Color{0, 0, 0, 0}
    {}
    constexpr Color(Uint8 r, Uint8 g, Uint8 b): SDL_Color{r, g, b, SDL_ALPHA_OPAQUE}
    {}
    constexpr Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a): SDL_Color{r, g, b, a}
    {}
    constexpr Color(const SDL_Color& color): SDL_Color{color.r, color.g, color.b, color.a}
    {}

    Color(const Color&) noexcept = default;

    Color(Color&&) noexcept = default;

    Color& operator=(const Color&) noexcept = default;

    Color& operator=(Color&&) noexcept = default;

    constexpr Uint8 red() const
    {
        return r;
    }

    void red(Uint8 rc)
    {
        r = rc;
    } 

    constexpr Uint8 green() const
    {
        return g;
    }

    void green(Uint8 gc)
    {
        g = gc;
    }

    constexpr Uint8 blue() const
    {
        return b;
    }

    void blue(Uint8 bc)
    {
        b = bc;
    }

    constexpr Uint8 alpha() const
    {
        return a;
    }

    void alpha(Uint8 ac)
    {
        a = ac;
    }

};

} // sdl2

constexpr bool operator==(const sdl2::Color& a, const sdl2::Color& b)
{
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

constexpr bool operator!=(const sdl2::Color& a, const sdl2::Color& b)
{
    return !(a == b);
}

std::ostream& operator<<(std::ostream& os, const sdl2::Color& color);

#endif