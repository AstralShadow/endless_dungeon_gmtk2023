#include "game/tick.hpp"
#include "game/hero.hpp"
#include "game/hints.hpp"
#include "game/tick.hpp"
#include "core/core.hpp"


void game::tick_hero(u32 ms)
{
    auto& hero = game::hero();
    auto& animation_pos = hero.animation_pos;


    bool is_idle = animation_pos.x == 0
                  && animation_pos.y == 0;

    if(!is_idle || hero.attacking) {
        float f_time = frames_per_second * ms / 1000;
        hero.frame += f_time;
        while(hero.frame >= 4)
            hero.frame -= 4;
    }

    if(is_idle || hero.attacking) {
        tick_hero_attack(ms);
    }

    if(!hero.attacking)
        tick_hero_movement(ms);


    hero.stamina += hero.stamina_regen * ms / 1000;
    if(hero.stamina > hero.max_stamina)
        hero.stamina = hero.max_stamina;

    if(hero.xp > hero.max_xp) {
        static int level = 0;
        switch(level) {
            case 0:
                activate_hint(H_LEVELUP_1);
                break;
            case 1:
                activate_hint(H_LEVELUP_2);
                break;
            case 2:
                activate_hint(H_LEVELUP_3);
                break;

            default:
                break;
        }
        level++;
        hero.xp -= hero.max_xp;
        hero.attack += 5;
        hero.max_health += 25;
        hero.max_stamina += 25;
        hero.health = hero.max_health;
        hero.stamina = hero.max_stamina;
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
