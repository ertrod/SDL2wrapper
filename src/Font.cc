#include "libs/SDL2_ttf/include/SDL_ttf.h"
#include "SDL2wrapper/include/Font.h"

#include <cassert>
#include <vector>
#include <optional>


#include "SDL2wrapper/include/Pointers.h"
#include "SDL2wrapper/include/Exception.h"
#include "SDL2wrapper/include/Surface.h"

namespace sdl2
{

Font::Font(TTF_Font* font) : font_(font) {
    assert(font);
}

Font::Font(const std::string& file, int ptsize, long index) {
    font_ = FontPtr(TTF_OpenFontIndex(file.c_str(), ptsize, index));
    if (font_ == nullptr)
        throw SDLException("TTF_OpenFontIndex");
}

Font::Font(Font&& other) noexcept 
    : font_(std::move(other.font_)) {
}

Font& Font::operator=(Font&& other) noexcept {
    if (&other == this)
        return *this;
    if (font_ != nullptr)
        TTF_CloseFont(font_.get());
    font_ = std::move(other.font_);
    return *this;
}

TTF_Font* Font::Get() const {
    return font_.get();
}

int Font::Style() const {
    return TTF_GetFontStyle(font_.get());
}

Font& Font::Style(int style) {
    TTF_SetFontStyle(font_.get(), style);
    return *this;
}

int Font::Outline() const {
    return TTF_GetFontOutline(font_.get());
}

Font& Font::Outline(int outline) {
    TTF_SetFontOutline(font_.get(), outline);
    return *this;
}

int Font::Hinting() const {
    return TTF_GetFontHinting(font_.get());
}

Font& Font::Hinting(int hinting) {
    TTF_SetFontHinting(font_.get(), hinting);
    return *this;
}

bool Font::Kerning() const {
    return TTF_GetFontKerning(font_.get()) > 0;
}

Font& Font::Kerning(bool allowed) {
    TTF_SetFontKerning(font_.get(), allowed);
    return *this;
}

int Font::Height() const {
    return TTF_FontHeight(font_.get());
}

int Font::Ascent() const {
    return TTF_FontAscent(font_.get());
}

int Font::Descent() const {
    return TTF_FontDescent(font_.get());
}

int Font::LineSkip() const {
    return TTF_FontLineSkip(font_.get());
}

long Font::NumFaces() const {
    return TTF_FontFaces(font_.get());
}

bool Font::IsMono() const {
    return TTF_FontFaceIsFixedWidth(font_.get()) > 0;
}

std::optional<std::string> Font::FamilyName() const {
    const char* str = TTF_FontFaceFamilyName(font_.get());
    if (str == nullptr)
        return std::nullopt;
    return std::string(str);
}

std::optional<std::string> Font::StyleName() const {
    const char* str = TTF_FontFaceStyleName(font_.get());
    if (str == nullptr)
        return std::nullopt;
    return std::string(str);
}

int Font::IsGlyphProvided(Uint16 ch) const {
    return TTF_GlyphIsProvided(font_.get(), ch);
}

void Font::GlyphMetrics(Uint16 ch, int& minx, int& maxx, int& miny, int& maxy, int& advance) const {
    if (TTF_GlyphMetrics(font_.get(), ch, &minx, &maxx, &miny, &maxy, &advance) != 0)
        throw SDLException("TTF_GlyphMetrics");
}

Rect Font::GlyphRect(Uint16 ch) const {
    int minx, maxx, miny, maxy;
    if (TTF_GlyphMetrics(font_.get(), ch, &minx, &maxx, &miny, &maxy, nullptr) != 0)
        throw SDLException("TTF_GlyphMetrics");
    return Rect(minx, miny, maxx - minx, maxy - miny);
}

int Font::GlyphAdvance(Uint16 ch) const {
    int advance;
    if (TTF_GlyphMetrics(font_.get(), ch, nullptr, nullptr, nullptr, nullptr, &advance) != 0)
        throw SDLException("TTF_GlyphMetrics");
    return advance;
}

Point Font::SizeOfText(const std::string& text) const {
    int w, h;
    if (TTF_SizeText(font_.get(), text.c_str(), &w, &h) != 0)
        throw SDLException("TTF_SizeText");
    return Point(w, h);
}

Point Font::SizeOfUTF8(const std::string& text) const {
    int w, h;
    if (TTF_SizeUTF8(font_.get(), text.c_str(), &w, &h) != 0)
        throw SDLException("TTF_SizeUTF8");
    return Point(w, h);
}

Point Font::SizeOfUnicode(const std::u16string& text) const {
    std::vector<Uint16> uint16_text(text.length() + 1);
    std::copy(text.begin(), text.end(), uint16_text.begin());
    return SizeOfUnicode(uint16_text.data());
}

Point Font::SizeOfUnicode(const Uint16* text) const {
    int w, h;
    if (TTF_SizeUNICODE(font_.get(), text, &w, &h) != 0)
        throw SDLException("TTF_SizeUNICODE");
    return Point(w, h);
}

Surface Font::RenderText_Solid(const std::string& text, SDL_Color fg) {
    SDL_Surface* surface = TTF_RenderText_Solid(font_.get(), text.c_str(), fg);
    if (surface == nullptr)
        throw SDLException("TTF_RenderText_Solid");
    return Surface(surface);
}

Surface Font::RenderUTF8_Solid(const std::string& text, SDL_Color fg) {
    SDL_Surface* surface = TTF_RenderUTF8_Solid(font_.get(), text.c_str(), fg);
    if (surface == nullptr)
        throw SDLException("TTF_RenderUTF8_Solid");
    return Surface(surface);
}

Surface Font::RenderUNICODE_Solid(const std::u16string& text, SDL_Color fg) {
    std::vector<Uint16> uint16_text(text.length() + 1);
    std::copy(text.begin(), text.end(), uint16_text.begin());
    return Font::RenderUNICODE_Solid(uint16_text.data(), fg);
}

Surface Font::RenderUNICODE_Solid(const Uint16* text, SDL_Color fg) {
    SDL_Surface* surface = TTF_RenderUNICODE_Solid(font_.get(), text, fg);
    if (surface == nullptr)
        throw SDLException("TTF_RenderUNICODE_Solid");
    return Surface(surface);
}

Surface Font::RenderGlyph_Solid(Uint16 ch, SDL_Color fg) {
    SDL_Surface* surface = TTF_RenderGlyph_Solid(font_.get(), ch, fg);
    if (surface == nullptr)
        throw SDLException("TTF_RenderGlyph_Solid");
    return Surface(surface);
}

Surface Font::RenderText_Shaded(const std::string& text, SDL_Color fg, SDL_Color bg) {
    SDL_Surface* surface = TTF_RenderText_Shaded(font_.get(), text.c_str(), fg, bg);
    if (surface == nullptr)
        throw SDLException("TTF_RenderText_Shaded");
    return Surface(surface);
}

Surface Font::RenderUTF8_Shaded(const std::string& text, SDL_Color fg, SDL_Color bg) {
    SDL_Surface* surface = TTF_RenderUTF8_Shaded(font_.get(), text.c_str(), fg, bg);
    if (surface == nullptr)
        throw SDLException("TTF_RenderUTF8_Shaded");
    return Surface(surface);
}

Surface Font::RenderUNICODE_Shaded(const std::u16string& text, SDL_Color fg, SDL_Color bg) {
    std::vector<Uint16> uint16_text(text.length() + 1);
    std::copy(text.begin(), text.end(), uint16_text.begin());
    return Font::RenderUNICODE_Shaded(uint16_text.data(), fg, bg);
}

Surface Font::RenderUNICODE_Shaded(const Uint16* text, SDL_Color fg, SDL_Color bg) {
    SDL_Surface* surface = TTF_RenderUNICODE_Shaded(font_.get(), text, fg, bg);
    if (surface == nullptr)
        throw SDLException("TTF_RenderUNICODE_Shaded");
    return Surface(surface);
}

Surface Font::RenderGlyph_Shaded(Uint16 ch, SDL_Color fg, SDL_Color bg) {
    SDL_Surface* surface = TTF_RenderGlyph_Shaded(font_.get(), ch, fg, bg);
    if (surface == nullptr)
        throw SDLException("TTF_RenderGlyph_Shaded");
    return Surface(surface);
}

Surface Font::RenderText_Blended(const std::string& text, SDL_Color fg) {
    SDL_Surface* surface = TTF_RenderText_Blended(font_.get(), text.c_str(), fg);
    if (surface == nullptr)
        throw SDLException("TTF_RenderText_Blended");
    return Surface(surface);
}

Surface Font::RenderUTF8_Blended(const std::string& text, SDL_Color fg) {
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font_.get(), text.c_str(), fg);
    if (surface == nullptr)
        throw SDLException("TTF_RenderUTF8_Blended");
    return Surface(surface);
}

Surface Font::RenderUNICODE_Blended(const std::u16string& text, SDL_Color fg) {
    std::vector<Uint16> uint16_text(text.length() + 1);
    std::copy(text.begin(), text.end(), uint16_text.begin());
    return Font::RenderUNICODE_Blended(uint16_text.data(), fg);
}

Surface Font::RenderUNICODE_Blended(const Uint16* text, SDL_Color fg) {
    SDL_Surface* surface = TTF_RenderUNICODE_Blended(font_.get(), text, fg);
    if (surface == nullptr)
        throw SDLException("TTF_RenderUNICODE_Blended");
    return Surface(surface);
}

Surface Font::RenderGlyph_Blended(Uint16 ch, SDL_Color fg) {
    SDL_Surface* surface = TTF_RenderGlyph_Blended(font_.get(), ch, fg);
    if (surface == nullptr)
        throw SDLException("TTF_RenderGlyph_Blended");
    return Surface(surface);
}

} // sdl2