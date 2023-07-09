#ifndef INCLUDE_GAME_HERO_HPP
#define INCLUDE_GAME_HERO_HPP

#include "utils/types.hpp"
#include "utils/point.hpp"
#include "game/entity.hpp"


namespace game
{
    struct Hero : public Entity
    {
        Hero();

        /* Stats */
        float health = 100;
        float max_health = 100;
        float stamina = 100;
        float max_stamina = 100;
        float stamina_regen = 15;
        float xp = 10;
        float max_xp = 50;

        int attack = 15;


        float speed = 128; // world px/s
        //float dash_speed = 192;

        //float hunger = 100; // [0, 100]

        //float morale = 50;
        //float min_morale = 0;
        //float max_morale = 100;

        //int money = 30;


        float frame = 0;
        bool attacking = false;
        int attack_mode = 0;
    };

    Hero& hero();

    extern int defeated_enemies;
}

#endif // INCLUDE_GAME_HERO_HPP
