#include "SDL2wrapper/include/Rect.h"

#include <algorithm>
#include <optional>

#include "SDL2wrapper/include/Point.h"

namespace sdl2
{

Rect Rect::Union(const Rect& rect) const
{
    return Rect::FromCorners(
            std::min(x, rect.x),
            std::min(y, rect.y),
            std::max(X2(), rect.X2()),
            std::max(Y2(), rect.Y2())
        );
}

Rect& Rect::MakeUnionWith(const Rect& rect)
{
    x = std::min(x, rect.x);
    y = std::min(y, rect.y);
    X2(std::max(X2(), rect.X2()));
    Y2(std::max(Y2(), rect.Y2()));
    return *this;
}

Rect Rect::Extension(unsigned int amount) const
{
    Rect r = *this;
    r.Extend(amount);
    return r;
}

Rect Rect::Extension(unsigned int hamount, unsigned int vamount) const
{
    Rect r = *this;
    r.Extend(hamount, vamount);
    return r;
}

Rect& Rect::Extend(unsigned int amount)
{
    return Extend(amount, amount);
}

Rect& Rect::Extend(unsigned int hamount, unsigned int vamount)
{
    x -= hamount;
    y -= vamount;
    w += hamount * 2;
    h += vamount * 2;
    return *this;
}

std::optional<Rect> Rect::GetIntersection(const Rect& rect) const
{
    if (!Intersects(rect))
        return std::nullopt;
    return Rect::FromCorners(
            std::max(x, rect.x),
            std::max(y, rect.y),
            std::min(X2(), rect.X2()),
            std::min(Y2(), rect.Y2())
        );
}

bool Rect::IntersectsLine(int& x1, int& y1, int& x2, int& y2) const {
    return SDL_IntersectRectAndLine(this, &x1, &y1, &x2, &y2) == SDL_TRUE;
}

bool Rect::IntersectsLine(Point& p1, Point& p2) const {
    return SDL_IntersectRectAndLine(this, &p1.x, &p1.y, &p2.x, &p2.y) == SDL_TRUE;
}

} // sdl2

std::ostream& operator<<(std::ostream& stream, const sdl2::Rect& rect) {
    stream << "[ x:" << rect.x << "; y:" << rect.y << "; w:" << rect.w << "; h:" << rect.h << " ]";
    return stream;
}

bool operator<(const sdl2::Rect& a, const sdl2::Rect& b) {
    return (a.h < b.h && a.w < b.w);
}