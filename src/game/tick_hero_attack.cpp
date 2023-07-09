#include "game/hero.hpp"
#include "game/level.hpp"
#include "game/enemy.hpp"
#include "game/tick.hpp"
#include "utils/types.hpp"
#include "utils/trandom.hpp"
#include <vector>
#include <iostream>

using std::cout;
using std::endl;

using std::vector;


void game::tick_hero_attack(u32)
{
    struct RNG_Token;

    auto& level = game::level();
    auto& hero = game::hero();

    auto& pos = hero.pos;
    auto& animation_pos = hero.animation_pos;


    bool finish_attack = false;

    Point target = pos;
    if(hero.attacking && hero.frame > 3) {
        if(animation_pos.x > 0) {
            target.x += 1;
            finish_attack = true;
        }

        if(animation_pos.x < 0) {
            target.x -= 1;
            finish_attack = true;
        }

        if(animation_pos.y > 0) {
            target.y += 1;
            finish_attack = true;
        }

        if(animation_pos.y < 0) {
            target.y -= 1;
            finish_attack = true;
        }
    }

    if(finish_attack) {
        animation_pos.x = 0;
        animation_pos.y = 0;
        hero.attacking = false;

        for(auto& enemy : enemies()) {
            if(target == enemy.pos) {
                enemy._health -= hero.attack;
            }
        }
    }

    if(hero.attacking)
        return;

    if(hero.stamina < 25)
        return;


    vector<Point> neighbours = {
        {pos.x - 1, pos.y},
        {pos.x + 1, pos.y},
        {pos.x, pos.y - 1},
        {pos.x, pos.y + 1}
    };

    for(auto p : neighbours) {
        Tile tile = level.at(p);
        if(tile.content == Tile::C_ENEMY) {
            hero.attacking = true;
            animation_pos.x = p.x - pos.x;
            animation_pos.y = p.y - pos.y;
            hero.frame = 0;
            hero.stamina -= 25;

            struct RNG_Token;
            hero.attack_mode = random<0, 2, RNG_Token>();
            break;
        }
    }

}

