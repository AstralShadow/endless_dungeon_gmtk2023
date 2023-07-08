#include "game/tick.hpp"
#include "game/hero.hpp"


void game::tick_hero(u32 ms)
{
    tick_hero_movement(ms);
}
