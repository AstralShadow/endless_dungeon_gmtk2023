#include "game/entity.hpp"
#include "game/level.hpp"
#include "game/navigation.hpp"
#include <iostream>

using std::cout;
using std::endl;

using game::Entity;


void Entity::move_to(Point _pos)
{
    if(this->c_type == Tile::C_HERO)
    if(!can_hero_walk_on(level().at(_pos.x, _pos.y))) {
        cout << "Tried to walk into wall" << endl;
        return;
    }
    if(this->c_type == Tile::C_ENEMY)
    if(!can_enemy_walk_on(level().at(_pos.x, _pos.y))) {
        cout << "Tried to walk into wall" << endl;
        return;
    }

    { /** Move away from current tile */
        Tile tile = level().at(pos.x, pos.y);
        tile.content = Tile::C_NONE;
        level().at(pos.x, pos.y).set(tile);
    }

    Point old_pos = pos;
    pos = _pos;

    { /** Move on next tile */
        Tile tile = level().at(pos.x, pos.y);

        // TODO: take tile.content

        tile.content = this->c_type;
        level().at(pos.x, pos.y).set(tile);
    }

    update_dijkstra_maps({pos, old_pos});
}

