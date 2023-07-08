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
            T_GROUND, // auto-generated
            T_PATH, // made by player

            T_LAST
        };

        Type type = T_WALL;


        enum Content : u8
        {
            C_NONE,
            C_HERO,
            
            C_LAST
        };

        Content content = C_NONE;

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

    inline Tile path_tile()
    {
        Tile tile;
        tile.type = Tile::T_PATH;
        return tile;
    }

    inline bool operator == (Tile a, Tile b)
    {
        return a.type == b.type
            && a.content == b.content;
    }
}

#endif // INCLUDE_TILE_HPP
