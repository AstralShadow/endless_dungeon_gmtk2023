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


        /* Dijkstra maps */
        u32 interest = 0xffffffff; // 0 = explored
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
        if(a.type != b.type || a.content != b.content)
            return false;

        return true;
    }

    inline bool operator != (Tile a, Tile b)
    {
        return !(a == b);
    }


    inline bool can_hero_walk_on(Tile a)
    {
        switch(a.type) {
            case Tile::T_GROUND:
            case Tile::T_PATH:
                break;
            default:
                return false;
        }

        switch(a.content) {
            default:
                return false;
        }

        return true;
    }

}

#endif // INCLUDE_TILE_HPP
