#ifndef INCLUDE_GAME_CAMERA_HPP
#define INCLUDE_GAME_CAMERA_HPP

#include "utils/point.hpp"


namespace game
{
    struct Camera
    {
        FPoint mid {16, 16};
        float zoom = 1.0f;

        Point pos();
        FPoint fpos();
        Point size();
        FPoint fsize();

        void apply(int& x, int& y);
        void apply(Point&);
        void apply(SDL_Rect&);
    };

    Camera& camera();

    const float camera_speed = 400.0f; // px/s
}

#endif // INCLUDE_GAME_CAMERA_HPP
