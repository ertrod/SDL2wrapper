#ifndef SDL2WRAPPER_EXCEPTION_H_
#define SDL2WRAPPER_EXCEPTION_H_

#include <stdexcept>
#include <string>

namespace sdl2
{

class SDLException : public std::runtime_error
{
private:
    static std::string make(const char* sdl_function, const char* sdl2_error);

public:
    explicit SDLException(const char* function);

    SDLException(const SDLException&) = default;

    virtual ~SDLException() noexcept;

    std::string SDLFunction() const;

    std::string SDLError() const;

private:
    std::string sdl_function_;
    std::string sdl_error_;
};

}

#endif