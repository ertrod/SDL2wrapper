
#include <memory>

#include "gtest/gtest.h"
#include "libs/SDL2/include/SDL.h"

#include "SDL2wrapper/include/Pointers.h"

TEST(SDL2wrapperPointersTestCase, SurfacePointersSizeEquality)
{
    EXPECT_EQ(
        sizeof(SDL_Surface*), sizeof(sdl2::SurfacePtr)
    );
    EXPECT_EQ(
        sizeof(std::shared_ptr<SDL_Surface>), sizeof(sdl2::SurfaceSharedPtr)
    );
}

TEST(SDL2wrapperPointersTestCase, TexturePointersSizeEquality)
{
    EXPECT_EQ(
        sizeof(SDL_Texture*), sizeof(sdl2::TexturePtr)
    );
    EXPECT_EQ(
        sizeof(std::shared_ptr<SDL_Texture>), sizeof(sdl2::TextureSharedPtr)
    );
}

TEST(SDL2wrapperPointersTestCase, RendererPointersSizeEquality)
{
    EXPECT_EQ(
        sizeof(SDL_Renderer*), sizeof(sdl2::RendererPtr)
    );
    EXPECT_EQ(
        sizeof(std::shared_ptr<SDL_Renderer>), sizeof(sdl2::RendererSharedPtr)
    );
}

TEST(SDL2wrapperPointersTestCase, WindowPointersSizeEquality)
{
    EXPECT_EQ(
        sizeof(SDL_Window*), sizeof(sdl2::WindowPtr)
    );
    EXPECT_EQ(
        sizeof(std::shared_ptr<SDL_Window>), sizeof(sdl2::WindowSharedPtr)
    );
}

TEST(SDL2wrapperPointersTestCase, RWopsPointersSizeEquality)
{
    EXPECT_EQ(
        sizeof(SDL_RWops*), sizeof(sdl2::RWopsPtr)
    );
    EXPECT_EQ(
        sizeof(std::shared_ptr<SDL_RWops>), sizeof(sdl2::RWopsSharedPtr)
    );
}