#include "game/hero.hpp"
#include "game/level.hpp"
#include "game/tick.hpp"
#include "utils/types.hpp"

using game::Hero;


void game::tick_hero_movement(u32 ms)
{
    float motion = hero_speed * ms / 1000;

    
}

