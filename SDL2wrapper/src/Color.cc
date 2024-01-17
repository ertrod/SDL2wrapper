#include "SDL2wrapper/include/Color.h"

#include <iostream>

std::ostream& operator<<(std::ostream& os, sdl2::Color& color)
{
    os << "[ r: " << color.r << "; g: " << color.g << "; b: " <<
        color.b << "; a: " << color.a << " ]";
    return os;
}