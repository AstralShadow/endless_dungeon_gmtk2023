#include "game/enemy.hpp"
#include "game/level.hpp"
#include "game/tick.hpp"
#include "utils/types.hpp"
#include "utils/trandom.hpp"
#include <vector>
#include <iostream>

using std::cout;
using std::endl;

using std::vector;


void game::tick_enemy_movement(u32 ms, Enemy& enemy)
{
    struct RNG_Token;

    auto& level = game::level();

    auto& pos = enemy.pos;
    auto& animation_pos = enemy.animation_pos;

    float motion = enemy.speed() * ms / 1000;

    bool reset_animation = false;

    if(animation_pos.x > tile_size.x) {
        enemy.move_to({
            pos.x + 1,
            pos.y
        });
        reset_animation = true;
    }

    if(animation_pos.x < -tile_size.x) {
        enemy.move_to({
            pos.x - 1,
            pos.y
        });
        reset_animation = true;
    }

    if(animation_pos.y > tile_size.y) {
        enemy.move_to({
            pos.x,
            pos.y + 1
        });
        reset_animation = true;
    }

    if(animation_pos.y < -tile_size.y) {
        enemy.move_to({
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
    if(false) // we allocate the tile on move start.
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
        if(!can_enemy_walk_on(other_tile)) {
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
    int min = dijkstra_max;

    for(u8 i = 0; i < neighbours.size(); ++i) {
        Tile tile = level.at(neighbours[i]);
        if(!can_enemy_walk_on(tile))
            continue;

        int value = tile.hero_path;
        if(value < min) {
            index = i;
            min = value;
        }
    }

    if(index == -1) {
        float random = randomf<RNG_Token>();
        for(u8 i = 0; i < neighbours.size(); ++i) {
            Tile tile = level.at(neighbours[i]);
            if(!can_enemy_walk_on(tile))
                continue;

            if(random < 0.25f * (i + 1)) {
                index = i;
                break;
            }
        }
    }

    if(index == -1)
        return;

    Point delta {
        neighbours[index].x - pos.x,
        neighbours[index].y - pos.y,
    };
    /* Allocate tile */ {
        Tile tile = level.at(neighbours[index].x,
                             neighbours[index].y);
        tile.content = Tile::C_ENEMY;
        level.at(neighbours[index].x,
                 neighbours[index].y) = tile;

        tile = level.at(pos.x, pos.y);
        tile.content = Tile::C_MOVING_ENEMY;
        level.at(pos.x, pos.y) = tile;

    }

    animation_pos.x += delta.x * motion;
    animation_pos.y += delta.y * motion;
}

