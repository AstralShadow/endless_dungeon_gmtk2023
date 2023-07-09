#include "game/hero.hpp"
#include "game/level.hpp"
#include "game/tick.hpp"
#include "utils/types.hpp"
#include <vector>
#include <iostream>

using std::cout;
using std::endl;

using std::vector;


void game::tick_hero_movement(u32 ms)
{
    auto& level = game::level();

    auto& hero = game::hero();
    auto& pos = hero.pos;
    auto& animation_pos = hero.animation_pos;

    float motion = hero.speed * ms / 1000;

    bool reset_animation = false;

    if(animation_pos.x > tile_size.x) {
        hero.move_to({
            pos.x + 1,
            pos.y
        });
        reset_animation = true;
    }

    if(animation_pos.x < -tile_size.x) {
        hero.move_to({
            pos.x - 1,
            pos.y
        });
        reset_animation = true;
    }

    if(animation_pos.y > tile_size.y) {
        hero.move_to({
            pos.x,
            pos.y + 1
        });
        reset_animation = true;
    }

    if(animation_pos.y < -tile_size.y) {
        hero.move_to({
            pos.x,
            pos.y - 1
        });
        reset_animation = true;
    }

    if(reset_animation) {
        animation_pos.x = 0;
        animation_pos.y = 0;
        return;
    }


    /* Fix walking into walls */
    {
        Point other = pos;
        if(animation_pos.x < 0)
            other.x -= 1;
        else if(animation_pos.x > 0)
            other.x += 1;
        else if(animation_pos.y < 0)
            other.y -= 1;
        else if(animation_pos.y > 0)
            other.y += 1;

        Tile other_tile = level.at(other);
        if(!can_hero_walk_on(other_tile)) {
            animation_pos.x = 0;
            animation_pos.y = 0;
        }   
    }

    bool is_idle = animation_pos.x == 0
                  && animation_pos.y == 0;

    if(!is_idle) {
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

    animation_pos.x += delta.x * motion;
    animation_pos.y += delta.y * motion;
}

