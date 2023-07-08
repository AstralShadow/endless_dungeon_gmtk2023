#ifndef INCLUDE_GAME_HERO_HPP
#define INCLUDE_GAME_HERO_HPP

#include "utils/types.hpp"
#include "utils/point.hpp"


namespace game
{
    struct Hero
    {
        Hero();

        Point pos{0, 0}; // in tiles
        FPoint animation_pos {0, 0}; // world pixels

        void move_to(Point pos); // tiles; no animation
    };

    Hero& hero();

    const float hero_speed = 64.0f; // pixels/s
}

#endif // INCLUDE_GAME_HERO_HPP
