#include "game/hero.hpp"
#include "game/level.hpp"
#include "game/tick.hpp"
#include "utils/types.hpp"
#include <vector>
#include <iostream>

using std::cout;
using std::endl;

using game::Hero;

using std::vector;


void game::tick_hero_movement(u32 ms)
{
    auto& hero = game::hero();
    auto& pos = hero.pos;
    auto& animation_pos = hero.animation_pos;

    float motion = hero_speed * ms / 1000;

    if(animation_pos.x > tile_size.x) {
        hero.move_to({
            pos.x + 1,
            pos.y
        });
        animation_pos.x -= tile_size.x;
    }

    if(animation_pos.x < -tile_size.x) {
        hero.move_to({
            pos.x - 1,
            pos.y
        });
        animation_pos.x += tile_size.x;
    }

    if(animation_pos.y > tile_size.y) {
        hero.move_to({
            pos.x,
            pos.y + 1
        });
        animation_pos.y -= tile_size.y;
    }

    if(animation_pos.y < -tile_size.y) {
        hero.move_to({
            pos.x,
            pos.y - 1
        });
        animation_pos.y += tile_size.y;
    }

    int is_idle = 2;

    if(std::abs(animation_pos.x) < 0.9 * motion) {
        animation_pos.x = 0;
        is_idle--;
    }
    if(std::abs(animation_pos.y) < 0.9 * motion) {
        animation_pos.y = 0;
        is_idle--;
    }

    if(is_idle != 0) {
        if(animation_pos.x < 0)
            animation_pos.x -= motion;
        else if(animation_pos.x > 0)
            animation_pos.x += motion;
        else if(animation_pos.y < 0)
            animation_pos.y -= motion;
        else if(animation_pos.y > 0)
            animation_pos.y += motion;

        return;
    }

    auto& level = game::level();

    vector<Point> neighbours = {
        {pos.x - 1, pos.y},
        {pos.x + 1, pos.y},
        {pos.x, pos.y - 1},
        {pos.x, pos.y + 1}
    };

    int index = -1;
    int max = 0;

    for(u8 i = 0; i < neighbours.size(); ++i) {
        Tile tile = level.at(neighbours[i]);
        if(!can_hero_walk_on(tile))
            continue;

        int value = tile.interest_path;
        if(value > max) {
            index = i;
            max = value;
        }
    }

    if(index == -1)
        return;

    Point delta {
        neighbours[index].x - pos.x,
        neighbours[index].y - pos.y,
    };

    cout << delta.x << ":" << delta.y << endl;
    cout << motion << endl;

    animation_pos.x += delta.x * motion;
    animation_pos.y += delta.y * motion;
}

