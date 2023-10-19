#ifndef SDL2WRAPPER_RENDERER_H_
#define SDL2WRAPPER_RENDERER_H_

#include <optional>

#include "libs/SDL2/include/SDL_stdinc.h"
#include "libs/SDL2/include/SDL_blendmode.h"

#include "SDL2wrapper/include/Pointers.h"
#include "SDL2wrapper/include/Point.h"
#include "SDL2wrapper/include/Color.h"
#include "SDL2wrapper/include/Rect.h"
#include "SDL2wrapper/include/Window.h"
#include "SDL2wrapper/include/Texture.h"

namespace sdl2
{

class Renderer
{
public:
    explicit Renderer(SDL_Renderer* renderer);

    Renderer(Window& window, int index, Uint32 flags);

    Renderer(Renderer&& other) noexcept;
    Renderer& operator=(Renderer&& other) noexcept;

    Renderer(const Renderer& other) = delete;
    Renderer& operator=(const Renderer& other) = delete;

    SDL_Renderer* Get() const;

    Renderer& Present();

    Renderer& Clear();

    void GetInfo(SDL_RendererInfo& info);

    Renderer& Copy(Texture& texture, 
        const std::optional<Rect>& srcrect = std::nullopt, 
        const std::optional<Rect>& dstrect = std::nullopt
    );
    Renderer& Copy(Texture& texture,
        const std::optional<Rect>& srcrect,
        const Point& dstpoint
    );
    Renderer& Copy(Texture& texture,
        const std::optional<Rect>& srcrect,
        const std::optional<Rect>& dstrect,
        double angle,
        const std::optional<Point>& center = std::nullopt,
        int flip = 0
    );
    Renderer& Copy(Texture& texture,
        const std::optional<Rect>& srcrect,
        const Point& dstpoint,
        double angle,
        const std::optional<Point>& center = std::nullopt,
        int flip = 0
    );
    Renderer& FillCopy(Texture& texture,
        const std::optional<Rect>& srcrect = std::nullopt,
        const std::optional<Rect>& dstrect = std::nullopt,
        const Point& offset = Point(0, 0),
        int flip = 0
    );

    Renderer& SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
    Renderer& SetDrawColor(const Color& color);

    Renderer& Target();
    Renderer& Target(Texture& texture);

    Renderer& DrawBlendMode(SDL_BlendMode blend = SDL_BLENDMODE_NONE);

    Renderer& DrawPoint(int x, int y);
    Renderer& DrawPoint(const Point& p);
    Renderer& DrawPoints(const Point* points, int count);

    Renderer& DrawLine(int x1, int y1, int x2, int y2);
    Renderer& DrawLine(const Point& start, const Point& end);
    Renderer& DrawLines(const Point* points, int count);

    Renderer& DrawRect(int x1, int y1, int x2, int y2);
    Renderer& DrawRect(const Point& top_left, const Point& bottom_right);
    Renderer& DrawRect(const Rect& rect);
    Renderer& DrawRects(const Rect* rects, int count);

    Renderer& FillRect(int x1, int y1, int x2, int y2);
    Renderer& FillRect(const Point& top_left, const Point& bottom_right);
    Renderer& FillRect(const Rect& rect);
    Renderer& FillRects(const Rect* rects, int count);

    void ReadPixels(const std::optional<Rect>& rect, Uint32 format, void* pixels, int pitch);

    Renderer& ClipRect(const std::optional<Rect>& rect);
    Renderer& LogicalSize(int w, int h);
    Renderer& Scale(float scaleX, float scaleY);
    Renderer& Viewport(const std::optional<Rect>& rect);

    bool TargetSupported() const;

    std::optional<Rect> ClipRect() const;
    Point LogicalSize() const;
    int LogicalWidth() const;
    int LogicalHeight() const;
    void Scale(float* scaleX, float* scaleY);
    float XScale() const;
    float YScale() const;
    Rect Viewport() const;
    SDL_BlendMode BlendMode() const;
    Color GetDrawColor();
    void GetDrawColor(Uint8& r, Uint8& g, Uint8& b, Uint8& a);
    Point OutputSize() const;
    int OutputWidth() const;
    int OutputHeight() const;
private:
    RendererPtr renderer_;
};

Texture CreateTexture(Renderer& renderer, Uint32 format, int access, int w, int h);
#ifdef SDL2WRAPPER_IMAGE
Texture CreateTexture(Renderer& renderer, const std::string& filename);
#endif
Texture CreateTexture(Renderer& renderer, const Surface& surface);

} // sdl2

#endif