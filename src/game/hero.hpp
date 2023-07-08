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


        /* Stats */
        float health = 100;
        float max_health = 100;
        float stamina = 100;
        float max_stamina = 100;
        float xp = 0;
        float max_xp = 100;

        float hunger = 100; // [0, 100]

        float speed = 64; // world px/s
        float dash_speed = 96;

        float morale = 50;
        float min_morale = 0;
        float max_morale = 100;

        int money = 30;
    };

    Hero& hero();
}

#endif // INCLUDE_GAME_HERO_HPP
