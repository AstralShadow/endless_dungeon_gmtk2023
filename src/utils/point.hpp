#ifndef INCLUDE_UTILS_POINT_HPP
#define INCLUDE_UTILS_POINT_HPP

#include <SDL2/SDL_rect.h>

typedef SDL_Point Point;
typedef SDL_FPoint FPoint;

constexpr bool operator == (Point const& a,
                            Point const& b)
{
    return a.x == b.x && a.y == b.y;
}

constexpr bool operator != (Point const& a,
                            Point const& b)
{
    return !(a == b);
}


constexpr bool operator < (Point a, Point b)
{
    if(a.y != b.y)
        return a.y < b.y;
    return a.x < b.x;
}


constexpr Point operator + (Point a, Point const& b)
{
    a.x += b.x;
    a.y += b.y;
    return a;
}

constexpr Point operator - (Point a, Point const& b)
{
    a.x -= b.x;
    a.y -= b.y;
    return a;
}


constexpr FPoint operator + (FPoint a, FPoint const& b)
{
    a.x += b.x;
    a.y += b.y;
    return a;
}

constexpr FPoint operator - (FPoint a, FPoint const& b)
{
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

#endif // INCLUDE_UTILS_POINT_HPP
