#include <utility>
#include <algorithm>

#include "gtest/gtest.h"
#include "libs/SDL2/include/SDL_rect.h"

#include "SDL2wrapper/include/Rect.h"
#include "SDL2wrapper/include/Point.h"

using namespace sdl2;

class SDL2wrapperRectTestFixture : public ::testing::Test
{
protected:
    SDL2wrapperRectTestFixture() : a(1, 1, 2, 2), b(3, 3, 4, 4), 
        sdl_rect{1, 1, 1, 1}
    {}

    Rect r;
    Rect a;
    Rect b;
    SDL_Rect sdl_rect;
};

TEST_F(SDL2wrapperRectTestFixture, DefaultRectConstructor)
{
    EXPECT_EQ(r.x, 0);
    EXPECT_EQ(r.y, 0);
    EXPECT_EQ(r.w, 0);
    EXPECT_EQ(r.h, 0);
}

TEST_F(SDL2wrapperRectTestFixture, ParametrizedRectConstructor)
{
    EXPECT_TRUE(a.x > 0);
    EXPECT_TRUE(a.y > 0);
    EXPECT_TRUE(a.w > 0);
    EXPECT_TRUE(a.h > 0);
}

TEST_F(SDL2wrapperRectTestFixture, RectConstructorFromSDL_Rect)
{
    Rect sr(sdl_rect);
    EXPECT_EQ(sr.x, sdl_rect.x);
    EXPECT_EQ(sr.y, sdl_rect.y);
    EXPECT_EQ(sr.w, sdl_rect.w);
    EXPECT_EQ(sr.h, sdl_rect.h);
}

TEST(SDL2wrapperRectTest, RectConstructorFromPoints)
{
    Point start{6, 6};
    Point size{7, 7};
    Rect pointed(start, size);
    EXPECT_EQ(pointed.x, start.x);
    EXPECT_EQ(pointed.y, start.y);
    EXPECT_EQ(pointed.w, size.x);
    EXPECT_EQ(pointed.h, size.y);
}

TEST(SDL2wrapperRectTest, RectConstructorFromPointAndSize)
{
    Point start{6, 6};
    int width = 7;
    int height = 7;

    Rect half_pointed(start, width, height);
    EXPECT_EQ(half_pointed.x, start.x);
    EXPECT_EQ(half_pointed.y, start.y);
    EXPECT_EQ(half_pointed.w, width);
    EXPECT_EQ(half_pointed.h, height);
}

class SDL2wrapperRectFromCenterTest : public ::testing::Test
{
protected:
    SDL2wrapperRectFromCenterTest() : 
        expected{5, 5}, center{10, 10}, size{10, 10}
    {}

    Point expected;
    Point center;
    Point size;
};

TEST_F(SDL2wrapperRectFromCenterTest, RectFromCenterCoordinates)
{
    Rect expanded = Rect::FromCenter(center.x, center.y, size.x, size.y);
    EXPECT_EQ(expected.x, expanded.x);
    EXPECT_EQ(expected.y, expanded.y);
    EXPECT_EQ(expanded.w, size.x);
    EXPECT_EQ(expanded.h, size.y);
}

TEST_F(SDL2wrapperRectFromCenterTest, RectFromCenterPoints)
{
    Rect expanded = Rect::FromCenter(center, size);
    EXPECT_EQ(expected.x, expanded.x);
    EXPECT_EQ(expected.y, expanded.y);
    EXPECT_EQ(expanded.w, size.x);
    EXPECT_EQ(expanded.h, size.y);
}

TEST_F(SDL2wrapperRectFromCenterTest, RectFromCenterPointAndSize)
{
    Rect expanded = Rect::FromCenter(center, size.x, size.y);
    EXPECT_EQ(expected.x, expanded.x);
    EXPECT_EQ(expected.y, expanded.y);
    EXPECT_EQ(expanded.w, size.x);
    EXPECT_EQ(expanded.h, size.y);
}

class SDL2wrapperRectFromCorners : public ::testing::Test
{
protected:
    SDL2wrapperRectFromCorners() :
        top_left{1, 1}, bottom_right{3, 3}
    {}
    Point top_left;
    Point bottom_right;
};

TEST_F(SDL2wrapperRectFromCorners, CreateFromPointsTest)
{
    Rect expanded = Rect::FromCorners(top_left, bottom_right);

    int expected_width = bottom_right.y - top_left.y + 1;
    int expected_height = bottom_right.x - top_left.x + 1;
    EXPECT_EQ(expanded.x, top_left.x);
    EXPECT_EQ(expanded.y, top_left.y);
    EXPECT_EQ(expanded.w, expected_width);
    EXPECT_EQ(expanded.h, expected_height);
}

TEST_F(SDL2wrapperRectFromCorners, CreateFromCoordinatesTest)
{
    Rect expanded = Rect::FromCorners(
        top_left.x, top_left.y, 
        bottom_right.x, bottom_right.y
    );

    int expected_width = bottom_right.y - top_left.y + 1;
    int expected_height = bottom_right.x - top_left.x + 1;
    EXPECT_EQ(expanded.x, top_left.x);
    EXPECT_EQ(expanded.y, top_left.y);
    EXPECT_EQ(expanded.w, expected_width);
    EXPECT_EQ(expanded.h, expected_height);
}

class SDL2wrapperRectOperations : public ::testing::Test
{
protected:
    SDL2wrapperRectOperations():
        a{1, 1, 5, 5}, b{2, 2, 6, 6}
    {}

    Rect a;
    Rect b;
};

TEST_F(SDL2wrapperRectOperations, AssignmentTest)
{
    Rect c = a;
    EXPECT_EQ(c.x, a.x);
    EXPECT_EQ(c.y, a.y);
    EXPECT_EQ(c.w, a.w);
    EXPECT_EQ(c.h, a.h);
}

TEST_F(SDL2wrapperRectOperations, GetX)
{
    EXPECT_EQ(a.X(), a.x);
}

TEST_F(SDL2wrapperRectOperations, SetX)
{
    int nx = 10;
    a.X(nx);
    EXPECT_EQ(a.x, nx);
}

TEST_F(SDL2wrapperRectOperations, GetY)
{
    EXPECT_EQ(a.Y(), a.y);
}

TEST_F(SDL2wrapperRectOperations, SetY)
{
    int ny = 10;
    a.Y(ny);
    EXPECT_EQ(a.y, ny);
}

TEST_F(SDL2wrapperRectOperations, GetW)
{
    EXPECT_EQ(a.W(), a.w);
}

TEST_F(SDL2wrapperRectOperations, SetW)
{
    int nw = 10;
    a.W(nw);
    EXPECT_EQ(a.w, nw);
}

TEST_F(SDL2wrapperRectOperations, GetH)
{
    EXPECT_EQ(a.H(), a.h);
}

TEST_F(SDL2wrapperRectOperations, SetH)
{
    int nh = 10;
    a.H(nh);
    EXPECT_EQ(a.h, nh);
}

TEST_F(SDL2wrapperRectOperations, GetX2)
{
    EXPECT_EQ(a.X2(), a.x + a.w -1);
}

TEST_F(SDL2wrapperRectOperations, SetX2)
{
    int nx2 = 10;
    a.X2(nx2);
    EXPECT_EQ(a.w, nx2 - a.x + 1);
}

TEST_F(SDL2wrapperRectOperations, GetY2)
{
    EXPECT_EQ(a.Y2(), a.y + a.h - 1);
}

TEST_F(SDL2wrapperRectOperations, SetY2)
{
    int nx2 = 10;
    a.X2(nx2);
    EXPECT_EQ(a.w, nx2 - a.x + 1);
}

TEST_F(SDL2wrapperRectOperations, GetTopLeft)
{
    Point expected{a.x, a.y};
    EXPECT_EQ(a.TopLeft(), expected);
}

TEST_F(SDL2wrapperRectOperations, GetTopRight)
{
    Point expected{a.X2(), a.y};
    EXPECT_EQ(a.TopRight(), expected);
}

TEST_F(SDL2wrapperRectOperations, GetBottomLeft)
{
    Point expected{a.x, a.Y2()};
    EXPECT_EQ(a.BottomLeft(), expected);
}

TEST_F(SDL2wrapperRectOperations, GetBottomRight)
{
    Point expected{a.X2(), a.Y2()};
    EXPECT_EQ(a.BottomRight(), expected);
}

TEST_F(SDL2wrapperRectOperations, GetCenter)
{
    Point expected{a.x + a.w/2, a.y + a.h/2};
    EXPECT_EQ(a.Center(), expected);
}

TEST_F(SDL2wrapperRectOperations, ContainsPosition)
{
    EXPECT_FALSE(a.Contains(-1, -1));
    EXPECT_FALSE(a.Contains(0, 0));
    EXPECT_TRUE(a.Contains(1, 1));
    EXPECT_TRUE(a.Contains(2, 2));
    EXPECT_TRUE(a.Contains(5, 5));
    EXPECT_FALSE(a.Contains(6, 6));
}

TEST_F(SDL2wrapperRectOperations, ContainsPoint)
{
    Point minused{-1, -1};
    Point outside_before{0, 0};
    Point top_border{1, 1};
    Point inside{2, 2};
    Point bottom_border{5, 5};
    Point outside_after{6, 6};

    EXPECT_FALSE(a.Contains(minused));
    EXPECT_FALSE(a.Contains(outside_before));
    EXPECT_TRUE(a.Contains(top_border));
    EXPECT_TRUE(a.Contains(inside));
    EXPECT_TRUE(a.Contains(bottom_border));
    EXPECT_FALSE(a.Contains(outside_after));
}

TEST_F(SDL2wrapperRectOperations, ContainsRect)
{
    Rect inside{2, 2, 1, 1};
    Rect outside{10, 10, 1, 1};

    EXPECT_FALSE(a.Contains(outside));
    EXPECT_TRUE(a.Contains(inside));
}

TEST_F(SDL2wrapperRectOperations, IntersectsWithRect)
{
    EXPECT_TRUE(a.Intersects(b));
    Rect c{7, 7, 2, 2};
    EXPECT_FALSE(a.Intersects(c));
    Rect same_as_a = a;
    EXPECT_TRUE(a.Intersects(same_as_a));
}

TEST_F(SDL2wrapperRectOperations, GetUnion)
{
    Rect expected{
        std::min(a.x, b.x),
        std::min(a.y, b.y),
        std::max(a.X2(), b.X2()),
        std::max(a.Y2(), b.Y2())
    };
    EXPECT_EQ(a.Union(b), expected);
}

TEST_F(SDL2wrapperRectOperations, MakeUnion)
{
    Rect expected{
        std::min(a.x, b.x),
        std::min(a.y, b.y),
        std::max(a.X2(), b.X2()),
        std::max(a.Y2(), b.Y2())
    };
    a.MakeUnionWith(b);
    EXPECT_EQ(a, expected);
}

TEST_F(SDL2wrapperRectOperations, Extension)
{
    int ha = 2;
    int va = 2;
    Rect expected_a{a.x - ha, a.y - va, a.w + ha*2, a.h + va*2};
    Rect extended_a = a.Extension(ha, va);

    EXPECT_EQ(extended_a, expected_a);

    ha = 1;
    va = 2;
    Rect expected_b{b.x - ha, b.y - va, b.w + ha*2, b.h + va*2};
    Rect extended_b = b.Extension(ha, va);

    EXPECT_EQ(extended_b.x, expected_b.x);
    EXPECT_EQ(extended_b.y, expected_b.y);
    EXPECT_EQ(extended_b.w, expected_b.w);
    EXPECT_EQ(extended_b.h, expected_b.h);
}

TEST_F(SDL2wrapperRectOperations, GetIntersection)
{
    Rect expected = Rect::FromCorners(
            std::max(a.x, b.x),
            std::max(a.y, b.y),
            std::min(a.X2(), b.X2()),
            std::min(a.Y2(), b.Y2())
        );
    std::optional<Rect> intersection = a.GetIntersection(b);
    EXPECT_EQ(expected, intersection.value_or(Rect{0, 0, -1, -1}));

    expected = {0, 0, -1, -1};
    Rect c = {10, 10 , 1, 1};
    std::optional<Rect> empty_intersection = a.GetIntersection(c);
    EXPECT_EQ(expected, empty_intersection.value_or(expected));
}

TEST_F(SDL2wrapperRectOperations, IntersectsLine)
{
    Point p1 = {3, 1};
    Point p2 = {4, 5};

    EXPECT_TRUE(a.IntersectsLine(p1, p2));
    EXPECT_TRUE(a.IntersectsLine(p1.x, p1.y, p2.x, p2.y));

    p1 = {100, 100};
    p2 = {101, 101};
    EXPECT_FALSE(a.IntersectsLine(p1, p2));
    EXPECT_FALSE(a.IntersectsLine(p1.x, p1.y, p2.x, p2.y));
}

TEST_F(SDL2wrapperRectOperations, MoveRect)
{
    Point offset{1, 1};
    Rect expected{b.x - offset.x, b.y - offset.y, b.w, b.h};
    EXPECT_EQ(b - offset, expected);

    expected = { b.x + offset.x, b.y + offset.y, b.w, b.h};
    EXPECT_EQ(b + offset, expected);
}