#ifndef SDL2WRAPPER_FONT_H_
#define SDL2WRAPPER_FONT_H_

#include <string>
#include <optional>

#include "SDL/SDL2_ttf/include/SDL_ttf.h"

#include "SDL2wrapper/include/Pointers.h"
#include "SDL2wrapper/include/Point.h"
#include "SDL2wrapper/include/Surface.h"
#include "SDL2wrapper/include/Rect.h"

namespace sdl2
{

class Font
{
public:
    explicit Font(TTF_Font* font);
    Font(const std::string& file, int ptsize, long index = 0);

    Font(Font&& other) noexcept;
    Font& operator=(Font&& other) noexcept;

    Font(const Font&) = delete;
    Font& operator=(const Font&) = delete;

    TTF_Font* Get() const;
    
    int Style() const;
    Font& Style(int style);

    int Outline() const;
    Font& Outline(int outline);

    int Hinting() const;
    Font& Hinting(int hinting);

    bool Kerning() const;
    Font& Kerning(bool allowed);

    int Height() const;
    int Ascent() const;
    int Descent() const;
    int LineSkip() const;
    long NumFaces() const;
    bool IsMono() const;
    std::optional<std::string> FamilyName() const;
    std::optional<std::string> StyleName() const;
    int IsGlyphProvided(Uint16 ch) const;
    void GlyphMetrics(Uint16 ch, int& minx, int& maxx, int& miny, int& maxy, int& advance) const;
    Rect GlyphRect(Uint16 ch) const;
    int GlyphAdvance(Uint16 ch) const;
    Point SizeOfText(const std::string& text) const;
    Point SizeOfUTF8(const std::string& text) const;
    Point SizeOfUnicode(const Uint16* text) const;
    Point SizeOfUnicode(const std::u16string& text) const;

    Surface RenderText_Solid(const std::string& text, SDL_Color fg);
    Surface RenderUTF8_Solid(const std::string& text, SDL_Color fg);
    Surface RenderUNICODE_Solid(const std::u16string& text, SDL_Color fg);
    Surface RenderUNICODE_Solid(const Uint16* text, SDL_Color fg);
    Surface RenderGlyph_Solid(Uint16 ch, SDL_Color fg);

    Surface RenderText_Shaded(const std::string& text, SDL_Color fg, SDL_Color bg);
    Surface RenderUTF8_Shaded(const std::string& text, SDL_Color fg, SDL_Color bg);
    Surface RenderUNICODE_Shaded(const std::u16string& text, SDL_Color fg, SDL_Color bg);
    Surface RenderUNICODE_Shaded(const Uint16* text, SDL_Color fg, SDL_Color bg);
    Surface RenderGlyph_Shaded(Uint16 ch, SDL_Color fg, SDL_Color bg);

    Surface RenderText_Blended(const std::string& text, SDL_Color fg);
    Surface RenderUTF8_Blended(const std::string& text, SDL_Color fg);
    Surface RenderUNICODE_Blended(const std::u16string& text, SDL_Color fg);
    Surface RenderUNICODE_Blended(const Uint16* text, SDL_Color fg);
    Surface RenderGlyph_Blended(Uint16 ch, SDL_Color fg);
private:
    FontPtr font_;
};

}

#endif