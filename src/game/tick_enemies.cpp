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


    for(Enemy& enemy : enemies)
        tick_enemy_movement(ms, enemy);
}
