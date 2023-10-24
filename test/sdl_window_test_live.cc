#include <iostream>

#include "gtest/gtest.h"
#include "libs/SDL2/include/SDL.h"

#include "SDL2wrapper/include/Point.h"
#include "SDL2wrapper/include/Window.h"

using namespace sdl2;

TEST(SDL2wrapperWindowTestLive, WindowComponents)
{
    SDL_Init(SDL_INIT_VIDEO);

    Window window("sdl2wrapper test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 240, SDL_WINDOW_RESIZABLE);

    SDL_Delay(1000);
    
    {
        EXPECT_EQ(window.Size(), Point(320, 240));
        EXPECT_EQ(window.Width(), 320);
        EXPECT_EQ(window.Height(), 240);
        
        window.Size(400, 300);
        EXPECT_EQ(window.Size(), Point(400, 300));
        EXPECT_EQ(window.Width(), 400);
        EXPECT_EQ(window.Height(), 300);
        SDL_Delay(1000);

        window.Size(500, 400);
        EXPECT_EQ(window.Size(), Point(500, 400));
        EXPECT_EQ(window.Width(), 500);
        EXPECT_EQ(window.Height(), 400);
        SDL_Delay(1000);
    }

    {
        EXPECT_EQ(window.Title(), "sdl2wrapper test");

        window.Title("sdl2wrapper window test");
        EXPECT_EQ(window.Title(), "sdl2wrapper window test");
        SDL_Delay(1000);
    }

    {
        EXPECT_EQ(
            window.DrawableSize(), 
            Point(window.DrawableWidth(), window.DrawableHeight())
        );
        
        EXPECT_TRUE(window.DrawableWidth() >= window.Width());
        EXPECT_TRUE(window.DrawableHeight() >= window.Height());
        EXPECT_TRUE(window.DrawableWidth() > window.DrawableHeight());
    }

    {
        window.MinimumSize(16, 16);
        window.MaximumSize(1600, 1000);

        EXPECT_EQ(window.MinimumSize(), Point(16, 16));
        EXPECT_EQ(window.MaximumSize(), Point(1600, 1000));

        window.MinimumSize(Point(32, 32));
        window.MaximumSize(Point(1920, 1080));

        EXPECT_EQ(window.MinimumSize(), Point(32, 32));
        EXPECT_EQ(window.MaximumSize(), Point(1920, 1080));
    }

    {
        EXPECT_FALSE(window.Grab());
        window.Grab(true);
        EXPECT_TRUE(window.Grab());

        SDL_Delay(1000);
        window.Grab(false);
        EXPECT_FALSE(window.Grab());
        SDL_Delay(1000);
    }

    // {
    //     EXPECT_EQ(window.Brightness(), 1.0f);

    //     window.Brightness(1.2f);
    //     EXPECT_EQ(window.Brightness(), 1.2f);
    //     SDL_Delay(1000);

    //     window.Brightness(1.f);
    //     EXPECT_EQ(window.Brightness(), 1.0f);
    //     SDL_Delay(1000);
    // }

    {
        std::cerr << "Window flags: " << std::hex << "0x" << window.Flags() << std::dec << std::endl;

        EXPECT_EQ(window.Flags() & SDL_WINDOW_SHOWN, SDL_WINDOW_SHOWN);

        window.Hide();
        EXPECT_EQ(window.Flags() & SDL_WINDOW_SHOWN, 0U);
        SDL_Delay(1000);

        window.Show();
        EXPECT_EQ(window.Flags() & SDL_WINDOW_SHOWN, SDL_WINDOW_SHOWN);
        SDL_Delay(1000);

        window.Maximize();
        EXPECT_EQ(window.Flags() & SDL_WINDOW_MAXIMIZED, SDL_WINDOW_MAXIMIZED);
        SDL_Delay(1000);

        window.Restore();
        EXPECT_EQ(window.Flags() & SDL_WINDOW_MAXIMIZED, 0U);
        SDL_Delay(1000);

        window.Minimize();
        SDL_Delay(1000);
        EXPECT_EQ(window.Flags() & SDL_WINDOW_MINIMIZED, SDL_WINDOW_MINIMIZED);
        SDL_Delay(1000);

        window.Restore();
        SDL_Delay(1000);
        EXPECT_EQ(window.Flags() & SDL_WINDOW_MINIMIZED, 0U);
        SDL_Delay(1000);

        window.Bordered(false);
        EXPECT_TRUE(window.Flags() & SDL_WINDOW_BORDERLESS);
        SDL_Delay(1000);

        window.Bordered(true);
        EXPECT_TRUE(!(window.Flags() & SDL_WINDOW_BORDERLESS));
        SDL_Delay(1000);

        window.Raise();
        SDL_Delay(1000);
    }
}