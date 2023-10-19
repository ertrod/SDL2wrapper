#include <utility>

#include "gtest/gtest.h"
#include "libs/SDL2/include/SDL_pixels.h"

#include "SDL2wrapper/include/Color.h"


using namespace sdl2;

class SDL2wrapperColorTest : public ::testing::Test
{
protected:

    SDL2wrapperColorTest(): 
        a(255, 255, 255), b(255, 255, 255, 0)
    {}

    void SetUp() override
    {
        // c uses default constructor
        sdl_color = {128, 128, 128, 255};
    }

    Color c;
    Color a;
    Color b;
    SDL_Color sdl_color;
};

TEST_F(SDL2wrapperColorTest, DefaultColorConstructor)
{
    EXPECT_EQ(c.r, 0);
    EXPECT_EQ(c.g, 0);
    EXPECT_EQ(c.b, 0);
    EXPECT_EQ(c.a, 0);
}

TEST_F(SDL2wrapperColorTest, ParametrizedColorConstructor)
{
    EXPECT_TRUE(a.r >= 0);
    EXPECT_TRUE(a.g >= 0);
    EXPECT_TRUE(a.b >= 0);
    EXPECT_TRUE(a.a >= 0);
}

TEST_F(SDL2wrapperColorTest, ParametrizedColorConstructorWithAlpha)
{
    EXPECT_NE(b.r, 0);
    EXPECT_NE(b.g, 0);
    EXPECT_NE(b.b, 0);
    EXPECT_EQ(b.a, 0);
}

TEST_F(SDL2wrapperColorTest, ColorConstructorFromSDL_Color)
{
    Color wrapped_color(sdl_color);
    EXPECT_EQ(wrapped_color.r, sdl_color.r);
    EXPECT_EQ(wrapped_color.g, sdl_color.g);
    EXPECT_EQ(wrapped_color.b, sdl_color.b);
    EXPECT_EQ(wrapped_color.a, sdl_color.a);
}

TEST_F(SDL2wrapperColorTest, ColorCopyConstructor)
{
    Color a_copy(a);
    EXPECT_EQ(a_copy.r, a.r);
    EXPECT_EQ(a_copy.g, a.g);
    EXPECT_EQ(a_copy.b, a.b);
    EXPECT_EQ(a_copy.a, a.a);
}

TEST_F(SDL2wrapperColorTest, ColorMoveConstructor)
{
    Color a_moved(std::move(a));
    EXPECT_EQ(a_moved.r, a.r);
    EXPECT_EQ(a_moved.g, a.g);
    EXPECT_EQ(a_moved.b, a.b);
    EXPECT_EQ(a_moved.a, a.a);
}

TEST_F(SDL2wrapperColorTest, ColorCopyAssignment)
{
    Color copied = a;
    EXPECT_EQ(copied.r, a.r);
    EXPECT_EQ(copied.g, a.g);
    EXPECT_EQ(copied.b, a.b);
    EXPECT_EQ(copied.a, a.a);
}

TEST_F(SDL2wrapperColorTest, GetRedColor)
{
    Uint8 red = a.red();
    EXPECT_EQ(red, a.r);
}

TEST_F(SDL2wrapperColorTest, SetRedColor)
{
    Uint8 red_value = 20;
    a.red(red_value);
    EXPECT_EQ(a.r, red_value);
}

TEST_F(SDL2wrapperColorTest, GetGreenColor)
{
    Uint8 green = a.green();
    EXPECT_EQ(green, a.g);
}

TEST_F(SDL2wrapperColorTest, SetGreenColor)
{
    Uint8 green_value = 20;
    a.green(green_value);
    EXPECT_EQ(a.g, green_value);
}

TEST_F(SDL2wrapperColorTest, GetBlueColor)
{
    Uint8 blue = a.blue();
    EXPECT_EQ(blue, a.b);
}

TEST_F(SDL2wrapperColorTest, SetBlueColor)
{
    Uint8 blue_value = 20;
    a.blue(blue_value);
    EXPECT_EQ(a.b, blue_value);
}

TEST_F(SDL2wrapperColorTest, GetAlpha)
{
    Uint8 alpha = a.alpha();
    EXPECT_EQ(alpha, a.a);
}

TEST_F(SDL2wrapperColorTest, SetAlpha)
{
    Uint8 alpha_value = 20;
    a.alpha(alpha_value);
    EXPECT_EQ(a.a, alpha_value);
}

TEST_F(SDL2wrapperColorTest, ColorEquality)
{
    EXPECT_FALSE(a == b);
}

TEST_F(SDL2wrapperColorTest, ColorUnequality)
{
    EXPECT_TRUE(a != b);
}
