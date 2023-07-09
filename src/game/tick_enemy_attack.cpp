#include "game/enemy.hpp"
#include "game/level.hpp"
#include "game/hero.hpp"
#include "game/tick.hpp"
#include "utils/types.hpp"
#include "utils/trandom.hpp"
#include <vector>
#include <iostream>

using std::cout;
using std::endl;

using std::vector;


void game::tick_enemy_attack(u32, Enemy& enemy)
{
    if(enemy.type == ET_GHOST)
        return;

    struct RNG_Token;

    auto& level = game::level();
    auto& hero = game::hero();

    auto& pos = enemy.pos;
    auto& animation_pos = enemy.animation_pos;


    bool finish_attack = false;

    Point target = pos;
    if(enemy.attacking && enemy.frame > 3) {
        if(animation_pos.x > 0) {
            target.x += 1;
            finish_attack = true;
        }

        if(animation_pos.x < 0) {
            target.x -= 1;
            finish_attack = true;
        }
    }

    if(finish_attack) {
        animation_pos.x = 0;
        animation_pos.y = 0;
        enemy.attacking = false;

        if(target == hero.pos) {
            hero.health -= enemy.attack();
        }
    }

    if(enemy.attacking)
        return;



    vector<Point> neighbours = {
        {pos.x - 1, pos.y},
        {pos.x + 1, pos.y}
    };

    for(auto p : neighbours) {
        Tile tile = level.at(p);
        if(tile.content == Tile::C_HERO) {
            enemy.attacking = true;
            animation_pos.x = p.x - pos.x;
            enemy.frame = 0;
            break;
        }
    }

}

