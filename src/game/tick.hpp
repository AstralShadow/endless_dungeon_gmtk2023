#ifndef INCLUDE_GAME_TICK_HPP
#define INCLUDE_GAME_TICK_HPP

#include "utils/types.hpp"
#include "game/navigation.hpp"

namespace game
{
    struct Enemy;

    void tick_move_camera(u32);

    void tick_hero(u32);
    void tick_hero_movement(u32);

    void tick_enemies(u32);
    void tick_enemy_movement(u32, Enemy&);

    extern int speed_mode;
}

#endif // INCLUDE_GAME_TICK_HPP
