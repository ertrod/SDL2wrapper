#ifndef SDL2WRAPPER_SURFACE_H_
#define SDL2WRAPPER_SURFACE_H_

#include <optional>

#include "libs/SDL2/include/SDL_stdinc.h"
#include "libs/SDl2/include/SDL_blendmode.h"

#include "SDL2wrapper/include/Rect.h"
#include "SDL2wrapper/include/Point.h"
#include "SDL2wrapper/include/Color.h"
#include "SDL2wrapper/include/Pointers.h"

namespace sdl2
{

class Surface 
{
public:
    class LockHandle
    {
        friend class Surface;
    private:
        
        explicit LockHandle(Surface& surface);

    public:
        LockHandle();
        ~LockHandle();

        LockHandle(LockHandle&& other) noexcept;

        LockHandle& operator=(LockHandle&& other) noexcept;

        LockHandle(const LockHandle& other) = delete;
        LockHandle& operator=(const LockHandle& other) = delete;

        void* Pixels() const;
        int Pitch() const;
        const SDL_PixelFormat& Format() const;

    private:
        SurfaceSharedPtr surface_;

    };

    explicit Surface(SDL_Surface* surface);

    Surface(Uint32 flags, int width, int height, int depth, 
        Uint32 Rm, Uint32 Gm, Uint32 Bm, Uint32 Am);
    
    Surface(void* pixels, int width, int height, int depth, 
        int pitch, Uint32 Rm, Uint32 Gm, Uint32 Bm, Uint32 Am);
    
#ifdef SDL2WRAPPER_IMAGE
    
    explicit Surface(const std::string& filename);

#endif


    Surface(Surface&& other) noexcept;

    Surface& operator=(Surface&& other) noexcept;

    Surface(const Surface&) = delete;
    Surface& operator=(const Surface&) = delete;

    SDL_Surface* Get() const;

    Surface Convert(const SDL_PixelFormat& format);
    Surface Convert(Uint32 pixel_format);

    void Blit(const std::optional<Rect>& srcrect, Surface& dst, const Rect& dstrect);
    void BlitScaled(const std::optional<Rect>& srcrect, Surface& dst, const std::optional<Rect>& dstrect);

    LockHandle Lock();

    Uint32 ColorKey() const;
    Surface& ColorKey(bool flag, Uint32 key);

    Uint8 AlphaMod() const;
    Surface& AlphaMod(Uint8 alpha);

    SDL_BlendMode BlendMode() const;
    Surface& BlendMode(SDL_BlendMode blendMode);

    Color ColorAndAlphaMod() const;
    Surface& ColorAndAlphaMod(const Color& color);

    void ColorMod(Uint8& r, Uint8& g, Uint8& b) const;
    Surface& ColorMod(Uint8 r = 255, Uint8 g = 255, Uint8 b = 255);

    Rect ClipRect() const;
    Surface& ClipRect(const std::optional<Rect>& rect = std::nullopt);

    Surface& RLE(bool flag);

    Surface& FillRect(const std::optional<Rect>& rect, Uint32 color);
    Surface& FillRects(const Rect* rects, int count, Uint32 color);

    int Width() const;
    int Height() const;

    Uint32 Format() const;

private:
    SurfaceSharedPtr surface_;
};

} // sdl2

#endif