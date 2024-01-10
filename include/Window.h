#ifndef SDL2WRAPPER_WINDOW_H_
#define SDL2WRAPPER_WINDOW_H_

#include "SDL/SDL2/include/SDL_version.h"
#include "SDL/SDL2/include/SDL_stdinc.h"
#include "SDL/SDL2/include/SDL_video.h"

#include "SDL2wrapper/include/Pointers.h"
#include "SDL2wrapper/include/Surface.h"


namespace sdl2
{

class Window
{
public:
    Window(const std::string& title, int x, int y, int w, int h, Uint32 flags);

    Window(Window&& other) = delete;
    Window& operator=(Window&& other) = delete;

    Window(const Window& other) = delete;
    Window& operator=(const Window& other) = delete;

    SDL_Window* Get() const;

    Point Size() const;
    int Width() const;
    int Height() const;

    Point DrawableSize() const;
    int DrawableWidth() const;
    int DrawableHeight() const;

    Window& Title(const std::string& title);
    std::string Title() const;

    Window& Maximize();
    Window& Minimize();
    Window& Hide();
    Window& Restore();
    Window& Raise();
    Window& Show();
    Window& Fullscreen(Uint32 flags);

    Window& Size(int w, int h);
    Window& Size(const Point& size);

    float Brightness() const;
    Window& Brightness(float brightness);

    Point Position() const;
    Window& Position(int x, int y);
    Window& Position(const Point& pos);

    Point MinimumSize() const;
    Window& MinimumSize(int x, int h);
    Window& MinimumSize(const Point& size);

    Point MaximumSize() const;
    Window& MaximumSize(int x, int h);
    Window& MaximumSize(const Point& size);

    bool Grab() const;
    Window& Grab(bool grabbed);

    int DisplayIndex() const;
    void DisplayMode(SDL_DisplayMode& mode) const;

    Uint32 Flags() const;

    Window& Icon(const Surface& icon);

    Window& Bordered(bool bordered = true);
private:
    WindowPtr window_;
};

} // sdl2


#endif