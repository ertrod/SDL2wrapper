#include "gtest/gtest.h"
#include "libs/SDL2/include/SDL_main.h" 
#include "libs/SDL2_ttf/include/SDL_ttf.h"

#include "SDL2wrapper/include/Exception.h"
#include "SDL2wrapper/include/SDLTTF.h"
#include "SDL2wrapper/include/Font.h"

using namespace sdl2;

TEST(SDL2wrapperFontTest, ComplexTest)
{
    SDLTTF ttf;
    Font font("Vera.ttf", 30);

    {
        // Font style
        font.Style(TTF_STYLE_NORMAL);
        EXPECT_EQ(font.Style(), TTF_STYLE_NORMAL);

        font.Style(TTF_STYLE_BOLD | TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE | TTF_STYLE_STRIKETHROUGH);
        EXPECT_EQ(font.Style(), TTF_STYLE_BOLD | TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE | TTF_STYLE_STRIKETHROUGH);

        font.Style(TTF_STYLE_NORMAL);
        EXPECT_EQ(font.Style(), TTF_STYLE_NORMAL);
    }

    {
        // Outline
        EXPECT_EQ(font.Outline(), 0);

        font.Outline(2);
        EXPECT_EQ(font.Outline(), 2);

        font.Outline(0);
        EXPECT_EQ(font.Outline(), 0);
    }

    {
        // Hinting
        font.Hinting(TTF_HINTING_NORMAL);
        EXPECT_EQ(font.Hinting(), TTF_HINTING_NORMAL);

        font.Hinting(TTF_HINTING_LIGHT);
        EXPECT_EQ(font.Hinting(), TTF_HINTING_LIGHT);

        font.Hinting(TTF_HINTING_NORMAL);
        EXPECT_EQ(font.Hinting(), TTF_HINTING_NORMAL);
    }

    {
        // Kerning
        font.Kerning(true);
        EXPECT_EQ(font.Kerning(), true);

        font.Kerning(false);
        EXPECT_EQ(font.Kerning(), false);

        font.Kerning(true);
        EXPECT_EQ(font.Kerning(), true);
    }

    {
        // Metrics
        EXPECT_TRUE(font.Height() == 35 || font.Height() == 36);
        EXPECT_EQ(font.Ascent(), 28);
        EXPECT_EQ(font.Descent(), -7);
        EXPECT_EQ(font.LineSkip(), 35);
    }

    {
        // Faces
        EXPECT_EQ(font.NumFaces(), 1);
    }

    {
        // Fixed width
        EXPECT_EQ(font.IsMono(), false);
    }

    {
        // Names
        auto family = font.FamilyName();
        auto style = font.StyleName();

        EXPECT_TRUE(family && *family == "Bitstream Vera Sans");
        EXPECT_TRUE(style && *style == "Roman");
    }

    {
        // Glyphs provided
        EXPECT_TRUE(font.IsGlyphProvided(u'A') > 0);
    #ifndef _MSC_VER // MSVC has problems with unicode literals
        EXPECT_TRUE(font.IsGlyphProvided(u'¼') > 0);
        EXPECT_TRUE(font.IsGlyphProvided(u'л') == 0);
        EXPECT_TRUE(font.IsGlyphProvided(u'Ы') == 0);
    #endif
    }

    auto isAllowedARect = [](const Rect& r) {
        return r.x == 0 && r.y == 0 && r.w >= 20 && r.w <= 21 && r.h >= 22 && r.h <= 22;
    };

    auto isAllowedAADims = [](const Point& p) {
        return p.x >= 42 && p.x <= 43 && p.y >= 35 && p.y <= 36;
    };

    {
        // Glyph metrics
        int minx, maxx, miny, maxy, advance;

        // Why doesn't TTF_GlyphMetrics on non-existing glyph not return -1?!
        //EXPECT_EXCEPTION(font.GetGlyphMetrics(u'л', minx, maxx, miny, maxy, advance), Exception);

        EXPECT_NO_THROW(font.GlyphMetrics(u'A', minx, maxx, miny, maxy, advance));

        EXPECT_EQ(minx, 0);
        EXPECT_TRUE(maxx >= 20 && maxx <= 21);
        EXPECT_EQ(miny, 0);
        EXPECT_EQ(maxy, 22);
        EXPECT_EQ(advance, 21);

        EXPECT_TRUE(isAllowedARect(font.GlyphRect(u'A')));
        EXPECT_EQ(font.GlyphAdvance(u'A'), 21);

        // Text size
        EXPECT_TRUE(isAllowedAADims(font.SizeOfText("AA")));
        EXPECT_TRUE(isAllowedAADims(font.SizeOfUTF8(u8"AA")));
        EXPECT_TRUE(isAllowedAADims(font.SizeOfUnicode(u"AA")));
    }

    {
        // Rendering
        // XXX: add real pixel color tests
        EXPECT_TRUE(isAllowedAADims(font.RenderText_Solid("AA", SDL_Color{255, 255, 255, 255}).Size()));
        EXPECT_TRUE(isAllowedAADims(font.RenderUTF8_Solid(u8"AA", SDL_Color{255, 255, 255, 255}).Size()));
        EXPECT_TRUE(isAllowedAADims(font.RenderUNICODE_Solid(u"AA", SDL_Color{255, 255, 255, 255}).Size()));

        EXPECT_TRUE(isAllowedAADims(font.RenderText_Shaded("AA", SDL_Color{255, 255, 255, 255}, SDL_Color{0, 0, 0, 255}).Size()));
        EXPECT_TRUE(isAllowedAADims(font.RenderUTF8_Shaded(u8"AA", SDL_Color{255, 255, 255, 255}, SDL_Color{0, 0, 0, 255}).Size()));
        EXPECT_TRUE(isAllowedAADims(font.RenderUNICODE_Shaded(u"AA", SDL_Color{255, 255, 255, 255}, SDL_Color{0, 0, 0, 255}).Size()));

        EXPECT_TRUE(isAllowedAADims(font.RenderText_Blended("AA", SDL_Color{255, 255, 255, 255}).Size()));
        EXPECT_TRUE(isAllowedAADims(font.RenderUTF8_Blended(u8"AA", SDL_Color{255, 255, 255, 255}).Size()));
        EXPECT_TRUE(isAllowedAADims(font.RenderUNICODE_Blended(u"AA", SDL_Color{255, 255, 255, 255}).Size()));
    }
}