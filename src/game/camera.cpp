#include "game/camera.hpp"
#include "utils/screen.hpp"

using game::Camera;


Point Camera::pos()
{
    auto size = screen_size();

    // Bigger zoom => smaller view area
    size.x /= zoom;
    size.y /= zoom;

    return {
        mid.x - size.x / 2,
        mid.y - size.y / 2
    };
}

FPoint Camera::fpos()
{
    auto size = screen_size();

    return {
        mid.x - size.x / (zoom * 2),
        mid.y - size.y / (zoom * 2)
    };
}


void Camera::apply(int& x, int& y)
{
    auto _pos = pos();
    x -= _pos.x;
    y -= _pos.y;
}

void Camera::apply(Point& p)
{
    auto _pos = pos();
    p.x -= _pos.x;
    p.y -= _pos.y;
}

void Camera::apply(SDL_Rect& r)
{
    auto _pos = fpos();
    r.x -= _pos.x;
    r.y -= _pos.y;

    r.x *= zoom;
    r.y *= zoom;
    r.w *= zoom;
    r.h *= zoom;
}

