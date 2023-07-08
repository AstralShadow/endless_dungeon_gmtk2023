#include "game/navigation.hpp"
#include "game/level.hpp"
#include "game/hero.hpp"


bool game::update_tile_value(Point pos)
{
    auto& level = game::level();

    Tile tile = level.at(pos);
    if(tile == default_tile())
        return false;

    bool modified = false;

    if(pos == hero().pos)
        if(tile.interest != 0) {
            tile.interest = 0;
            modified = true;
        }

    if(modified) {
        level.at(pos).set(tile);
        return true;
    }

    return false;
}

