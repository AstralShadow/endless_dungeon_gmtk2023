#ifndef INCLUDE_TILE_HPP
#define INCLUDE_TILE_HPP

namespace game
{
    struct Tile
    {

    };

    inline Tile default_tile()
        { return {}; }

    inline bool operator == (Tile, Tile)
    {
        return true;
    }
}

#endif // INCLUDE_TILE_HPP
