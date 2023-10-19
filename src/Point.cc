#include "SDl2wrapper/include/Point.h"

#include <iostream>

std::ostream& operator<<(std::ostream& os, const sdl2::Point& point)
{
    os << "[ x:" << point.x << "; y: " << point.y << "]";
    return os;
}