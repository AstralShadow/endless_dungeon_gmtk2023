#ifndef INCLUDE_GAME_ENTITY_HPP
#define INCLUDE_GAME_ENTITY_HPP

#include "utils/types.hpp"
#include "utils/point.hpp"
#include "game/tile.hpp"


namespace game
{
    struct Entity
    {
        Point pos{0, 0}; // in tiles
        FPoint animation_pos {0, 0}; // world pixels

        void move_to(Point pos); // tiles; no animation

        Tile::Content c_type;

    protected:
        Entity(Tile::Content _c) : c_type(_c) { }
        ~Entity() = default;
    };
}

#endif // INCLUDE_GAME_ENTITY_HPP
