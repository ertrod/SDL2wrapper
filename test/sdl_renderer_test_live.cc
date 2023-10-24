#include <vector>
#include <optional>

#include "gtest/gtest.h"
#include "libs/SDL2/include/SDL.h"

#include "SDL2wrapper/include/SDL2wrapper.h"
#ifdef SDL2WRAPPER_IMAGE
#include "libs/SDL2_image/include/SDL_image.h"
#include "SDL2wrapper/include/SDLImage.h"
#endif

using namespace sdl2;

TEST(SDL2WrapperRendererTest, ComplexTest)
{
    SDL sdl(SDL_INIT_VIDEO);
    {
        // SDL initialization stuff
        EXPECT_TRUE(sdl.IsInitialized(SDL_INIT_VIDEO) > 0);

        sdl.CloseSub(SDL_INIT_VIDEO);

        EXPECT_TRUE(sdl.IsInitialized(SDL_INIT_VIDEO) == 0);

        sdl.InitSub(SDL_INIT_VIDEO);

        EXPECT_TRUE(sdl.IsInitialized(SDL_INIT_VIDEO) > 0);
    }

    Window window("libSDL2pp test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 240, 0);
    Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    {
        // Info
        SDL_RendererInfo info;

        EXPECT_NO_THROW(renderer.GetInfo(info));

        std::cerr << "Renderer name: " << info.name << std::endl;
        std::cerr << "Renderer flags: " << info.flags << std::endl;
        std::cerr << "Number of texture formats: " << info.num_texture_formats << std::endl;
        std::cerr << "Max texture width: " << info.max_texture_width << std::endl;
        std::cerr << "Max texture height: " << info.max_texture_height << std::endl;

        EXPECT_TRUE(info.max_texture_width > 0);
        EXPECT_TRUE(info.max_texture_height > 0);
    }

    {
        // Clear, draw color
        renderer.SetDrawColor(1, 2, 3);

        Uint8 r, g, b, a;
        renderer.GetDrawColor(r, g, b, a);
        EXPECT_TRUE(r == 1 && g == 2 && b == 3 && a == 255);

        renderer.Clear();

        renderer.Present();
        SDL_Delay(1000);
    }

    {
        // Draw points
        renderer.SetDrawColor(0,0,0);
        renderer.Clear();

        renderer.SetDrawColor(255, 128, 0);
        renderer.DrawPoint(10, 10);

        renderer.SetDrawColor(0, 255, 128);
        renderer.DrawPoint(Point(20, 20));

        renderer.SetDrawColor(128, 0, 255);
        Point points[] = { {30, 30} };
        renderer.DrawPoints(points, 1);

        renderer.Present();
        SDL_Delay(1000);
    }

    {
        // Draw lines
        renderer.SetDrawColor(0, 0, 0);
        renderer.Clear();

        renderer.SetDrawColor(255, 128, 0);
        renderer.DrawLine(10, 10, 10, 50);

        renderer.SetDrawColor(0, 255, 128);
        renderer.DrawLine(Point(20, 10), Point(20, 50));

        renderer.SetDrawColor(128, 0, 255);
        Point points[] = { {30, 10}, {40, 50} };
        renderer.DrawLines(points, 2);

        renderer.Present();
        SDL_Delay(1000);
    }

    {
        // Draw rects
        renderer.SetDrawColor(0, 0, 0);
        renderer.Clear();

        renderer.SetDrawColor(255, 128, 0);
        renderer.DrawRect(10, 10, 19, 19);

        renderer.SetDrawColor(0, 255, 128);
        renderer.DrawRect(Point(30, 10), Point(39, 19));

        renderer.SetDrawColor(128, 0, 255);
        renderer.DrawRect(Rect(10, 30, 10, 10));

        renderer.SetDrawColor(128, 192, 255);
        Rect rects[] = { {30, 30, 10, 10 } };
        renderer.DrawRects(rects, 1);

        renderer.Present();
        SDL_Delay(1000);
    }

    {
        // Fill rects
        renderer.SetDrawColor(0, 0, 0);
        renderer.Clear();

        renderer.SetDrawColor(255, 128, 0);
        renderer.FillRect(10, 10, 19, 19);

        renderer.SetDrawColor(0, 255, 128);
        renderer.FillRect(Point(30, 10), Point(39, 19));

        renderer.SetDrawColor(128, 0, 255);
        renderer.FillRect(Rect(10, 30, 10, 10));

        renderer.SetDrawColor(128, 192, 255);
        Rect rects[] = { {30, 30, 10, 10 } };
        renderer.FillRects(rects, 1);

        renderer.Present();
        SDL_Delay(1000);
    }

    {
        // Clip rect
        renderer.SetDrawColor(0, 0, 0);
        renderer.Clear();

        renderer.ClipRect(Rect(1, 1, 1, 1));

        renderer.SetDrawColor(255, 255, 255);
        renderer.FillRect(0, 0, 10, 10);

        EXPECT_TRUE(renderer.ClipRect() && renderer.ClipRect() == Rect(1, 1, 1, 1));

        renderer.ClipRect(std::nullopt);

        EXPECT_TRUE(!renderer.ClipRect());

        renderer.Present();
        SDL_Delay(1000);
    }

    {
        // Blend
        renderer.SetDrawColor(0, 0, 0);
        renderer.Clear();

        EXPECT_EQ(renderer.BlendMode(), SDL_BLENDMODE_NONE);

        renderer.DrawBlendMode(SDL_BLENDMODE_BLEND);
        EXPECT_EQ(renderer.BlendMode(), SDL_BLENDMODE_BLEND);

        renderer.SetDrawColor(255, 255, 255, 127);
        renderer.FillRect(10, 10, 19, 19);

        renderer.DrawBlendMode();
        EXPECT_EQ(renderer.BlendMode(), SDL_BLENDMODE_NONE);

        renderer.Present();
        SDL_Delay(1000);
    }

    if (renderer.TargetSupported()) {
        // Render target
        Texture target = CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 32, 32);

        EXPECT_EQ(target.Access(), SDL_TEXTUREACCESS_TARGET);

        renderer.Target(target);
        renderer.SetDrawColor(255, 1, 2);
        renderer.Clear();
        renderer.Present();

        renderer.Target();
        renderer.SetDrawColor(0, 0, 0);
        renderer.Clear();

        renderer.Copy(target);

        renderer.Present();
        SDL_Delay(1000);
    } else {
        std::cerr << "render target is not supported here, some tests were skipped" << std::endl;
    }
    
    
#ifdef SDL2WRAPPER_IMAGE
    {
        // Init
        SDLImage img(IMG_INIT_PNG);
        EXPECT_EQ(img.Formats(), IMG_INIT_PNG);

        img.Formats(IMG_INIT_JPG);
        EXPECT_EQ(img.Formats(), IMG_INIT_PNG | IMG_INIT_JPG);
    }

    {
        // Texture
        renderer.SetDrawColor(0, 0, 0);
        renderer.Clear();

        Texture texture = CreateTexture(renderer, "SDL2wrapper/test/crate.png");

        EXPECT_EQ(texture.Access(), SDL_TEXTUREACCESS_STATIC);
        EXPECT_EQ(texture.Width(), 32);
        EXPECT_EQ(texture.Height(), 32);
        EXPECT_EQ(texture.Size(), Point(32, 32));

        renderer.Copy(texture, std::nullopt, Point(0, 0));

        renderer.Present();
        SDL_Delay(1000);

        // Texture: fill copy
        renderer.SetDrawColor(0, 0, 0);
        renderer.Clear();

        renderer.FillCopy(texture, std::nullopt, Rect(0, 0, 48, 48), Point(16, 16), 0);

        renderer.Present();
        SDL_Delay(1000);

        // Texture: alpha blending/modulation
        renderer.SetDrawColor(0, 0, 0);
        renderer.Clear();

        EXPECT_EQ(texture.BlendMode(), SDL_BLENDMODE_NONE);
        texture.BlendMode(SDL_BLENDMODE_BLEND);
        EXPECT_EQ(texture.BlendMode(), SDL_BLENDMODE_BLEND);

        EXPECT_EQ((int)texture.AlphaMod(), 255);
        texture.AlphaMod(127);
        EXPECT_EQ((int)texture.AlphaMod(), 127);

        renderer.Copy(texture, std::nullopt, Point(0, 0));

        renderer.Present();
        SDL_Delay(1000);

        texture.BlendMode(SDL_BLENDMODE_NONE);
        EXPECT_EQ(texture.BlendMode(), SDL_BLENDMODE_NONE);
        texture.AlphaMod(255);
        EXPECT_EQ((int)texture.AlphaMod(), 255);

        // Texture: color modulation
        renderer.SetDrawColor(0, 0, 0);
        renderer.Clear();

        Uint8 r, g, b;
        texture.GetColorMod(r, g, b);
        EXPECT_EQ((int)r, 255);
        EXPECT_EQ((int)g, 255);
        EXPECT_EQ((int)b, 255);
        texture.SetColorMod(89, 241, 50);

        renderer.Copy(texture, std::nullopt, Point(0, 0));

        renderer.Present();
        SDL_Delay(1000);

        texture.SetColorMod(0, 0, 0);
        texture.GetColorMod(r, g, b);
        EXPECT_EQ((int)r, 0);
        EXPECT_EQ((int)g, 0);
        EXPECT_EQ((int)b, 0);
    }
#endif // SDL2WRAPPER_IMAGE
}