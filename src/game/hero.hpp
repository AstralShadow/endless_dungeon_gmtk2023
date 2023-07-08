#ifndef INCLUDE_GAME_HERO_HPP
#define INCLUDE_GAME_HERO_HPP

#include "utils/types.hpp"
#include "utils/point.hpp"


namespace game
{
    struct Hero
    {
        Hero(Point _pos);

        Point pos; // in tiles
        FPoint animation_pos {0, 0};
    };

    Hero& hero();
}

#endif // INCLUDE_GAME_HERO_HPP
