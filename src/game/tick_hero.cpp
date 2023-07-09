#include "game/tick.hpp"
#include "game/hero.hpp"


void game::tick_hero(u32 ms)
{
    tick_hero_movement(ms);

    auto& hero = game::hero();
    auto& animation_pos = hero.animation_pos;


    bool is_idle = animation_pos.x == 0
                  && animation_pos.y == 0;

    if(!is_idle) {
        float f_time = frames_per_second * ms / 1000;
        hero.frame += f_time;
        while(hero.frame >= 4)
            hero.frame -= 4;
    }
}
