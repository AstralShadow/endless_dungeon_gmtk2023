#include "game/hero.hpp"
#include "game/level.hpp"

using game::Hero;


Hero& game::hero()
{
    static Hero _hero({0, 0});
    return _hero;
}


Hero::Hero(Point _pos) :
    pos(_pos)
{
    Tile tile = level().at(_pos.x, _pos.y);
    tile.content = Tile::C_HERO;
    level().at(_pos.x, _pos.y) = tile;
}

