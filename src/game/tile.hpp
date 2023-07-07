#ifndef INCLUDE_TILE_HPP
#define INCLUDE_TILE_HPP

#include "utils/point.hpp"
#include "utils/types.hpp"

namespace game
{
    struct Tile
    {
        /**
         * Represents a single square on the map.
         * Size: 32x32 in world coords
         */
        enum Type : u8
        {
            T_WALL,
            T_GROUND,

            T_LAST
        };

        Type type = T_WALL;


    };

    const Point tile_size {32, 32};


    inline Tile default_tile()
        { return {}; }

    inline Tile ground_tile()
    {
        Tile tile;
        tile.type = Tile::T_GROUND;
        return tile;
    }

    inline bool operator == (Tile a, Tile b)
    {
        return a.type == b.type;
    }
}

#endif // INCLUDE_TILE_HPP
