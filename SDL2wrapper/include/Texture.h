#ifndef SDL2WRAPPER_TEXTURE_H_
#define SDL2WRAPPER_TEXTURE_H_

#include <string>
#include <optional>

#include "SDL2/include/SDL_stdinc.h"
#include "SDL2/include/SDL_blendmode.h"
#include "SDL2/include/SDL_render.h"

#include "SDL2wrapper/include/Pointers.h"
#include "SDL2wrapper/include/Color.h"
#include "SDL2wrapper/include/Rect.h"
#include "SDL2wrapper/include/Surface.h"

namespace sdl2
{


class Texture
{
public:
    class LockHandle
    {
        friend class Texture;

        LockHandle(Texture* texture, const std::optional<Rect>& rect);
    public:

        LockHandle();
        ~LockHandle();

        LockHandle(LockHandle&& other) noexcept;

        LockHandle& operator=(LockHandle&& other) noexcept;

        LockHandle(const LockHandle& other) = delete;
        LockHandle& operator=(const LockHandle& other) = delete;

        void* Pixels() const;
        int Pitch() const;
    private:
        Texture* texture_;
        void* pixels_;
        int pitch_;
    };

    explicit Texture(SDL_Texture* texture);


    Texture(Texture&& other) noexcept;

    Texture& operator=(Texture&& other) noexcept;

    Texture(const Texture& other) = delete;
    Texture& operator=(const Texture& other) = delete;

    SDL_Texture* Get() const;

    Texture& Update(const std::optional<Rect>& rect, const void* pixels, int pitch);
    Texture& Update(const std::optional<Rect>& rect, Surface& surface);
    Texture& Update(const std::optional<Rect>& rect, Surface&& surface);

    Texture& UpdateYUV(
        const std::optional<Rect>& rect,
        const Uint8* yplane, int ypitch,
        const Uint8* uplane, int upitch,
        const Uint8* vplane, int vpitch
    );

    Texture& BlendMode(SDL_BlendMode blendMode); // SDL_BLENDMODE_NONE
    Texture& AlphaMod(Uint8 alpha); // 255
    Texture& SetColorMod(Uint8 r, Uint8 g, Uint8 b);
    Texture& ColorAndAlphaMod(const Color& color); // Color{255, 255, 255, SDL_ALPHA_OPAQUE}

    LockHandle Lock(const std::optional<Rect>& rect = std::nullopt);

    Uint32 Format() const;
    int Access() const;
    int Width() const;
    int Height() const;
    Point Size() const;
    
    Uint8 AlphaMod() const;
    SDL_BlendMode BlendMode() const;
    void GetColorMod(Uint8& r, Uint8& g, Uint8& b);
    Color ColorAndAlphaMod();

private:
    TexturePtr texture_;
};

} // sdl2

#endif