#include "game/hero.hpp"
#include "game/level.hpp"
#include <iostream>

using std::cout;
using std::endl;

using game::Hero;


Hero& game::hero()
{
    static Hero _hero;
    return _hero;
}


Hero::Hero()
{

}

void Hero::move_to(Point _pos)
{
    if(!can_hero_walk_on(level().at(_pos.x, _pos.y))) {
        cout << "Tried to walk into wall" << endl;
        return;
    }

    { /** Move away from current tile */
        Tile tile = level().at(pos.x, pos.y);
        tile.content = Tile::C_NONE;
        level().at(pos.x, pos.y) = tile;
    }

    pos = _pos;

    { /** Move on next tile */
        Tile tile = level().at(pos.x, pos.y);

        // TODO: take tile.content

        tile.content = Tile::C_HERO;
        level().at(pos.x, pos.y) = tile;
    }
}

