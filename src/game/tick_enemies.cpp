#include "game/tick.hpp"
#include "game/enemy.hpp"
#include "game/hero.hpp"
#include "game/level.hpp"
#include <cmath>


void game::tick_enemies(u32 ms)
{
    auto& enemies = game::enemies();
    auto& hero = game::hero();
    auto& level = game::level();

    // Cleanup
    auto itr = enemies.begin();
    while(itr != enemies.end()) {

        if(itr->_health <= 0) {
            switch(itr->type) {
                case ET_GOBLIN:
                    hero.xp += 5;
                    break;
                case ET_GHOST:
                    hero.xp += 15;
                    break;
                case ET_LAST:
                    break;
            }
            defeated_enemies++;

            Tile tile = level.at(itr->pos);
            tile.content = Tile::C_NONE;
            level.at(itr->pos) = tile;

            itr = enemies.erase(itr);
            continue;
        }

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
