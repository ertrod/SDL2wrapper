#ifndef SDL2WRAPPER_RECT_H_
#define SDL2WRAPPER_RECT_H_

#include <optional>

#include "SDL2/include/SDL.h"
#include "SDL2wrapper/include/Point.h"

namespace sdl2
{

class Rect : public SDL_Rect
{
public:
    constexpr Rect() : SDL_Rect{0, 0, 0, 0}
    {}
    constexpr Rect(int x, int y, int w, int h) : SDL_Rect{x, y, w, h}
    {}
    constexpr Rect(const SDL_Rect& rect) : SDL_Rect{rect.x, rect.y, rect.w, rect.h}
    {}
    constexpr Rect(const Point& start, const Point& size) : 
        SDL_Rect{start.x, start.y, size.x, size.y}
    {}
    constexpr Rect(const Point& start, int w, int h) :
        SDL_Rect{start.x, start.y, w, h}
    {}
    Rect(const Rect&) noexcept = default;
    Rect(Rect&&) noexcept = default;

    static constexpr Rect FromCenter(const Point& center, int w, int h)
    {
        return FromCenter(center.x, center.y, w, h);
    }

    static constexpr Rect FromCenter(int cx, int cy, int w, int h)
    {
        return Rect(cx - w/2, cy - h/2, w, h);
    }

    static constexpr Rect FromCenter(const Point& center, const Point& size)
    {
        return Rect(center - size / 2, size);
    }

    static constexpr Rect FromCorners(const Point& tl, const Point& br)
    {
        return Rect(tl, br - tl + Point(1, 1));
    }

    static constexpr Rect FromCorners(int x1, int y1, int x2, int y2)
    {
        return Rect(x1, y1, x2-x1+1, y2-y1+1);
    }

    Rect& operator=(const Rect&) noexcept = default;
    Rect& operator=(Rect&&) noexcept = default;

    constexpr int X() const 
    {
        return x;
    }

    Rect& X(int nx)
    {
        x = nx;
        return *this;
    }

    constexpr int Y() const
    {
        return y;
    }

    Rect& Y(int ny)
    {
        y = ny;
        return *this;
    }

    constexpr int W() const
    {
        return w;
    }

    Rect& W(int nw)
    {
        w = nw;
        return *this;
    }

    constexpr int H() const 
    {
        return h;
    }

    Rect& H(int nh)
    {
        h = nh;
        return *this;
    }

    constexpr int X2() const
    {
        return x + w - 1;
    }

    Rect& X2(int nx2)
    {
        w = nx2 - x + 1;
        return *this;
    }

    constexpr int Y2() const
    {
        return y + h - 1;
    }

    Rect& Y2(int ny2)
    {
        h = ny2 - y + 1;
        return *this;
    }

    constexpr Point TopLeft() const
    {
        return Point(x, y);
    }

    constexpr Point TopRight() const
    {
        return Point(X2(), y);
    }

    constexpr Point BottomLeft() const
    {
        return Point(x, Y2());
    }

    constexpr Point BottomRight() const 
    {
        return Point(X2(), Y2());
    }

    constexpr Point Center() const
    {
        return Point(x + w/2, y + h/2);
    }

    constexpr bool Contains(int px, int py)
    {
        return px >= x && py >= y && px <= X2() && py <= Y2();
    }

    constexpr bool Contains(const Point& point) const
    {
        return point.x >= x && point.y >= y && point.x <= X2() && point.y <= Y2();
    }

    constexpr bool Contains(const Rect& rect) const 
    {
		return rect.x >= x && rect.y >= y && rect.X2() <= X2() && rect.Y2() <= Y2();
	}

    constexpr bool Intersects(const Rect& rect) const
    {
        return !(rect.X2() < x || rect.Y2() < y || rect.x > X2() || rect.y > Y2());
    }

    Rect Union(const Rect& rect) const;

    Rect& MakeUnionWith(const Rect& rect);

    Rect Extension(unsigned int amount) const;

    Rect Extension(unsigned int hamount, unsigned int vamount) const;

    Rect& Extend(unsigned int amount);

    Rect& Extend(unsigned int hamount, unsigned int vamount);

    std::optional<Rect> GetIntersection(const Rect& rect) const;

    bool IntersectsLine(int& x1, int& y1, int& x2, int& y2) const;

    bool IntersectsLine(Point& p1, Point& p2) const;

    constexpr Rect operator+(const Point& offset) const
    {
        return Rect(x + offset.x, y + offset.y, w, h);
    }

    constexpr Rect operator-(const Point& offset) const
    {
        return Rect(x - offset.x, y - offset.y, w, h);
    }

    Rect& operator+=(const Point& offset)
    {
        x += offset.x;
        y += offset.y;
        return *this;
    }

    Rect& operator-=(const Point& offset)
    {
        x -= offset.x;
        y -= offset.y;
        return *this;
    }
};

} // sdl2

constexpr bool operator==(const sdl2::Rect& a, const sdl2::Rect& b)
{
    return a.x == b.x && a.y == b.y && a.w == b.w && a.h == b.h;
}

constexpr bool operator!=(const sdl2::Rect& a, const sdl2::Rect& b)
{
    return !(a == b);
}

bool operator<(const sdl2::Rect& a, const sdl2::Rect& b);

std::ostream &operator<<(std::ostream& stream, const sdl2::Rect& rect);

#endif