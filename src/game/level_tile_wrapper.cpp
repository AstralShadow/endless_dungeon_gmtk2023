#include "game/level.hpp"
#include "game/tile.hpp"

using game::Level;


Level::TileWrapper::operator Tile()
{
    auto* chunk = parent->find_chunk(pos.x >> 4,
                                     pos.y >> 4);

    if(chunk == nullptr)
        return default_tile();

    u8 x = pos.x & 0x0f;
    u8 y = pos.y & 0x0f;
    u8 c_pos = y * 16 + x;

    return chunk->tiles[c_pos];
}

Level::TileWrapper&
Level::TileWrapper::operator = (Tile tile)
{
    auto _default = default_tile();

    auto* chunk = parent->find_chunk(pos.x >> 4,
                                     pos.y >> 4);

    if(chunk == nullptr && tile == _default)
        return *this;

    if(chunk == nullptr) {
        chunk = parent->get_chunk(pos.x >> 4,
                                  pos.y >> 4);
    }


    u8 x = pos.x & 0x0f;
    u8 y = pos.y & 0x0f;
    u8 c_pos = y * 16 + x;

    if(tile == chunk->tiles[c_pos])
        return *this;

    if(tile == _default) {
        chunk->active_tiles--;
        if(chunk->active_tiles == 0) {
            parent->remove_chunk(pos.x >> 4, pos.y >> 4);
            return *this;
        }
    } else if(chunk->tiles[c_pos] == _default) {
        chunk->active_tiles++;
    }

    chunk->tiles[c_pos] = tile;
    return *this;
}

