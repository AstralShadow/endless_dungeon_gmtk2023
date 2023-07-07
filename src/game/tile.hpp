#ifndef INCLUDE_TILE_HPP
#define INCLUDE_TILE_HPP

namespace game
{
    struct Tile
    {
        enum Type : u8
        {
            T_WALL,
            T_GROUND,

            T_LAST
        };

        Type type = T_WALL;


    };

    inline Tile default_tile()
        { return {}; }

    inline Tile ground_tile()
    {
        Tile tile;
        tile.type = Tile::T_GROUND;
        return tile;
    }

    inline bool operator == (Tile, Tile)
    {
        return true;
    }
}

#endif // INCLUDE_TILE_HPP
