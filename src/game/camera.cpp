#include "game/camera.hpp"
#include "utils/screen.hpp"

using game::Camera;


Camera& game::camera()
{
    static Camera _camera;
    return _camera;
}


Point Camera::pos()
{
    auto size = screen_size();

    // Bigger zoom => smaller view area
    size.x /= zoom;
    size.y /= zoom;

    return {
        static_cast<int>(mid.x - size.x / 2),
        static_cast<int>(mid.y - size.y / 2)
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


Point Camera::size()
{
    auto size = screen_size();
    return {
        static_cast<int>(size.x / zoom),
        static_cast<int>(size.y / zoom)
    };
}

FPoint Camera::fsize()
{
    auto size = screen_size();
    return {
        size.x / zoom,
        size.y / zoom
    };
}


void Camera::apply(int& x, int& y)
{
    auto _pos = pos();
    x = (x - _pos.x) * zoom;
    y = (y - _pos.y) * zoom;
}

void Camera::apply(Point& p)
{
    apply(p.x, p.y);
}

void Camera::apply(SDL_Rect& r)
{
    apply(r.x, r.y);
    r.w *= zoom;
    r.h *= zoom;
}


void Camera::undo(int& x, int& y)
{
    auto _pos = pos();
    x = x / zoom + _pos.x;
    y = y / zoom + _pos.y;
}

void Camera::undo(Point& p)
{
    undo(p.x, p.y);
}

void Camera::undo(SDL_Rect& r)
{
    undo(r.x, r.y);

    r.w /= zoom;
    r.h /= zoom;
}

