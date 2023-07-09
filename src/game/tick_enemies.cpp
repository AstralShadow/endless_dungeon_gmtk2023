#include "game/tick.hpp"
#include "game/enemy.hpp"
#include "game/hero.hpp"
#include <cmath>


void game::tick_enemies(u32 ms)
{
    auto& enemies = game::enemies();
    auto& hero = game::hero();

    // Cleanup
    auto itr = enemies.begin();
    while(itr != enemies.end()) {
        Point delta = {
            itr->pos.x - hero.pos.x,
            itr->pos.y - hero.pos.y
        };
        if(std::abs(delta.x) > 96) {
            itr = enemies.erase(itr);
            continue;
        }
        if(std::abs(delta.y) > 96) {
            itr = enemies.erase(itr);
            continue;
        }
        itr++;
    }


    for(Enemy& enemy : enemies) {
        auto anim_p = enemy.animation_pos;

        bool is_idle = anim_p.x == 0 && anim_p.y == 0;
        if(!is_idle || enemy.attacking) {
            float f_time = frames_per_second * ms / 1000;

            enemy.frame += f_time;
            while(enemy.frame >= 4)
                enemy.frame -= 4;
        }

        
        if(is_idle || enemy.attacking)
            tick_enemy_attack(ms, enemy);


        if(!enemy.attacking)
            tick_enemy_movement(ms, enemy);
    }
}
