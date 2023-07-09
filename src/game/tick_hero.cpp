#include "game/tick.hpp"
#include "game/hero.hpp"
#include "game/hints.hpp"
#include "game/tick.hpp"
#include "core/core.hpp"


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

    if(hero.health < 0) {
        static int counter = 0;
        switch(counter) {
            case 0:
                activate_hint(H_GAME_OVER_1);
                break;
            case 1:
                activate_hint(H_GAME_OVER_2);
                break;
            case 2:
                activate_hint(H_GAME_OVER_3);
                break;

            case 3:
            case 5:
            case 9:
                activate_hint(H_GAME_OVER_LOOP);
                break;

            case 10:
                activate_hint(H_GAME_OVER_END);
                break;

            default:
                break;
        }
        hero.health = 100;
        speed_mode = 0;
        counter++;
    }
}
