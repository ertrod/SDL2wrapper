#include "SDL2wrapper/include/Window.h"

#include "SDL2/include/SDL.h"

#include "SDL2wrapper/include/Pointers.h"
#include "SDL2wrapper/include/Point.h"
#include "SDL2wrapper/include/Exception.h"
#include "SDL2wrapper/include/Surface.h"

namespace sdl2
{


Window::Window(const std::string& title, int x, int y, int w, int h, Uint32 flags)
{
    window_ = WindowPtr(SDL_CreateWindow(title.c_str(), x, y ,w, h, flags));
    if (window_ == nullptr)
        throw SDLException("SDL_CreateWindow");
}

SDL_Window* Window::Get() const
{
    return window_.get();
}

Point Window::Size() const
{
    int w, h;
    SDL_GetWindowSize(&*window_, &w, &h);
    return Point(w, h);
}

int Window::Width() const
{
    int w;
    SDL_GetWindowSize(&*window_, &w, nullptr);
    return w;
}

int Window::Height() const
{
    int h;
    SDL_GetWindowSize(&*window_, nullptr, &h);
    return h;
}

Point Window::DrawableSize() const 
{
    int w, h;
    SDL_GL_GetDrawableSize(&*window_, &w, &h);
    return Point(w, h);
}

int Window::DrawableWidth() const
{
    int w;
    SDL_GL_GetDrawableSize(&*window_, &w, nullptr);
    return w;
}

int Window::DrawableHeight() const
{
    int h;
    SDL_GL_GetDrawableSize(&*window_, nullptr, &h);
    return h;
}

Window& Window::Title(const std::string& title)
{
    SDL_SetWindowTitle(&*window_, title.c_str());
    return *this;
}

std::string Window::Title() const
{
    return SDL_GetWindowTitle(&*window_);
}

Window& Window::Maximize()
{
    SDL_MaximizeWindow(&*window_);
    return *this;
}

Window& Window::Minimize()
{
    SDL_MinimizeWindow(&*window_);
    return *this;
}

Window& Window::Hide()
{
    SDL_HideWindow(&*window_);
    return *this;
}

Window& Window::Restore()
{
    SDL_RestoreWindow(&*window_);
    return *this;
}

Window& Window::Raise()
{
    SDL_RaiseWindow(&*window_);
    return *this;
}

Window& Window::Show()
{
    SDL_ShowWindow(&*window_);
    return *this;
}

Window& Window::Fullscreen(Uint32 flags)
{
    if (SDL_SetWindowFullscreen(&*window_, flags) != 0)
        throw SDLException("SDL_SetWindowFullscreen");
    return *this;
}

Window& Window::Size(int w, int h)
{
    SDL_SetWindowSize(&*window_, w, h);
    return *this;
}

Window& Window::Size(const Point& size)
{
    SDL_SetWindowSize(&*window_, size.x, size.y);
    return *this;
}

float Window::Brightness() const 
{
    return SDL_GetWindowBrightness(&*window_);
}

Window& Window::Brightness(float brightness)
{
    if (SDL_SetWindowBrightness(&*window_, brightness) != 0)
        throw SDLException("SDL_SetWindowBrightness");
    return *this;
}

Point Window::Position() const
{
    int x, y;
    SDL_GetWindowPosition(&*window_, &x, &y);
    return Point(x, y);
}

Window& Window::Position(int x, int y)
{
    SDL_SetWindowPosition(&*window_, x, y);
    return *this;
}

Window& Window::Position(const Point& pos)
{
    SDL_SetWindowPosition(&*window_, pos.x, pos.y);
    return *this;
}

Point Window::MinimumSize() const
{
    int w, h;
    SDL_GetWindowMinimumSize(&*window_, &w, &h);
    return Point(w, h);
}

Window& Window::MinimumSize(int w, int h)
{
    SDL_SetWindowMinimumSize(&*window_, w, h);
    return *this;
}

Window& Window::MinimumSize(const Point& size)
{
    SDL_SetWindowMinimumSize(&*window_, size.x, size.y);
    return *this;
}

Point Window::MaximumSize() const
{
    int w, h;
    SDL_GetWindowMaximumSize(&*window_, &w, &h);
    return Point(w, h);
}

Window& Window::MaximumSize(int w, int h)
{
    SDL_SetWindowMaximumSize(&*window_, w, h);
    return *this;
}

Window& Window::MaximumSize(const Point& size)
{
    SDL_SetWindowMaximumSize(&*window_, size.x, size.y);
    return *this;
}

bool Window::Grab() const
{
    return SDL_GetWindowGrab(&*window_) == SDL_TRUE;
}

Window& Window::Grab(bool grabbed)
{
    SDL_SetWindowGrab(&*window_, grabbed ? SDL_TRUE : SDL_FALSE);
    return *this;
}

int Window::DisplayIndex() const
{
    int index = SDL_GetWindowDisplayIndex(&*window_);
    if (index < 0)
        throw SDLException("SDL_GetWindowDisplayIndex");
    return index;
}

void Window::DisplayMode(SDL_DisplayMode& mode) const
{
    if (SDL_GetWindowDisplayMode(&*window_, &mode) != 0)
        throw SDLException("SDL_GetWindowDisplayMode");
}

Uint32 Window::Flags() const
{
	return SDL_GetWindowFlags(&*window_);
}

Window& Window::Icon(const Surface& icon)
{
	SDL_SetWindowIcon(&*window_, icon.Get());
	return *this;
}

Window& Window::Bordered(bool bordered)
{
	SDL_SetWindowBordered(&*window_, bordered ? SDL_TRUE : SDL_FALSE);
	return *this;
}

}