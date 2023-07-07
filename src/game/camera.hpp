#ifndef INCLUDE_GAME_CAMERA_HPP
#define INCLUDE_GAME_CAMERA_HPP

#include "utils/point.hpp"


namespace game
{
    struct Camera
    {
        Point mid; // pos
        float zoom;

        Point pos();
        FPoint fpos();

        void apply(int& x, int& y);
        void apply(Point&);
        void apply(SDL_Rect&);
    };
}

#endif // INCLUDE_GAME_CAMERA_HPP
