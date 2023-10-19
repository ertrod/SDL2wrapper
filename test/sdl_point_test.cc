#include <utility>

#include "gtest/gtest.h"
#include "libs/SDL2/include/SDL.h"

#include "SDL2wrapper/include/Point.h"

using namespace sdl2;

class SDL2wrapperPointTest : public ::testing::Test 
{
protected:

    SDL2wrapperPointTest():
        a(1, 1), b(2, 2)
    {}

    void SetUp() override
    {
        // p uses default constructor
        sdl_point = { 1, 1 };
    }

    Point p;
    Point a;
    Point b;
    SDL_Point sdl_point;
};

TEST_F(SDL2wrapperPointTest, DefaultPointConstructor)
{
    EXPECT_TRUE(p.x == 0 and p.y == 0);
}

TEST_F(SDL2wrapperPointTest, ParametrizedPointConstructor)
{
    EXPECT_TRUE(a.x != 0 and a.y != 0);
}

TEST_F(SDL2wrapperPointTest, CopyPointConstructor)
{
    Point copy(a);
    EXPECT_EQ(copy.x, a.x);
    EXPECT_EQ(copy.y, a.y);
}

TEST_F(SDL2wrapperPointTest, MovePointConstructor)
{
    Point moved_base(std::move(b));
    EXPECT_EQ(moved_base.x, b.x);
    EXPECT_EQ(moved_base.y, b.y);
}

TEST_F(SDL2wrapperPointTest, FromSDL_PointConstructor)
{
    Point point_wrapper(sdl_point);
    EXPECT_EQ(sdl_point.x, point_wrapper.x);
    EXPECT_EQ(sdl_point.y, point_wrapper.y);
}

TEST_F(SDL2wrapperPointTest, PointUnaryMinus)
{
    Point minused_a = -a;
    EXPECT_EQ(minused_a.x, -a.x);
    EXPECT_EQ(minused_a.y, -a.y);
}


TEST_F(SDL2wrapperPointTest, PointPlusPoint)
{
    Point c = a + b;
    EXPECT_EQ(c.x, (a.x + b.x));
    EXPECT_EQ(c.y, (a.y + b.y));
}

TEST_F(SDL2wrapperPointTest, PointMinusPoint)
{
    Point c = a - b;
    EXPECT_EQ(c.x, (a.x - b.x));
    EXPECT_EQ(c.y, (a.y - b.y));
}

TEST_F(SDL2wrapperPointTest, PointDivideInteger)
{
    Point c = a / 2;
    EXPECT_EQ(c.x, a.x/2);
    EXPECT_EQ(c.y, a.y/2);
}

TEST_F(SDL2wrapperPointTest, PointMultiplyInteger)
{
    Point c = a * 2;
    EXPECT_EQ(c.x, a.x*2);
    EXPECT_EQ(c.y, a.y*2);
}

TEST_F(SDL2wrapperPointTest, PointAdditionAssignment)
{
    a += b;
    EXPECT_EQ(a.x, (b.x+1));
    EXPECT_EQ(a.y, (b.y+1));
}

TEST_F(SDL2wrapperPointTest, PointSubtractionAssignment)
{
    b -= a;
    EXPECT_EQ(b.x, (a.x));
    EXPECT_EQ(b.y, (a.y));
}

TEST_F(SDL2wrapperPointTest, PointEquality)
{
    EXPECT_FALSE(a == b);
}

TEST_F(SDL2wrapperPointTest, PointUnequality)
{
    EXPECT_TRUE(a != b);
}