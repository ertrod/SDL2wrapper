#ifndef SDL2WRAPPER_POINT_H_
#define SDL2WRAPPER_POINT_H_

#include <iostream>

#include "libs/SDL2/include/SDL_rect.h"

namespace sdl2
{

class Point : public SDL_Point
{
public:
    constexpr Point() : SDL_Point{0, 0}
    {}

    constexpr Point(int x, int y) : SDL_Point{x, y}
    {}

    constexpr Point(const SDL_Point& point) : SDL_Point{point.x, point.y}
    {}

    Point(const Point&) noexcept = default;
    Point(Point&&) noexcept = default;

    Point& operator=(Point&&) noexcept = default;

    constexpr Point operator-() const 
    {
        return Point(-x, -y);
    }

    constexpr Point operator+(const Point& term) const
    {
        return Point(x + term.x, y + term.y);
    }

    constexpr Point operator-(const Point& term) const
    {
        return Point(x - term.x, y - term.y);
    }

    constexpr Point operator+=(const Point& term)
    {
        x += term.x;
        y += term.y;
        return *this;
    }

    constexpr Point operator-=(const Point& term)
    {
        x -= term.x;
        y -= term.y;
        return *this;
    }

    constexpr Point operator/(int value) const
    {
        return Point(x/value, y/value);
    }

    constexpr Point operator*(int value) const
    {
        return Point(x*value, y*value);
    }
};

} // sdl2

constexpr bool operator==(const sdl2::Point& a, const sdl2::Point& b)
{
    return a.x == b.x && a.y == b.y;
}

constexpr bool operator!=(const sdl2::Point& a, const sdl2::Point& b)
{
    return !(a == b);
}

std::ostream& operator<<(std::ostream& os, const sdl2::Point& point);


#endif