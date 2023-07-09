#include "game/level.hpp"
#include <stdexcept>
#include <cmath>

using game::Level;

Level::ChunkPos Level::hash_chunk_pos(int x, int y)
{
    
    ChunkPos pos = (y << 16) | (x & 0xffff);
    u32 _out = 0xffff0000;
    if(x >= 0 && (x & _out))
        throw std::runtime_error("Invalid chunk coords");
    if(y >= 0 && (y & _out))
        throw std::runtime_error("Invalid chunk coords");

    if(x < 0 && (x & _out) != _out)
        throw std::runtime_error("Invalid chunk coords");
    if(y < 0 && (y & _out) != _out)
        throw std::runtime_error("Invalid chunk coords");

    return pos;
}

Point Level::unhash_chunk_pos(ChunkPos pos)
{
    int x = static_cast<i16>(pos & 0xffff) << 4;
    int y = static_cast<i16>((pos & 0xffff0000) >> 16) << 4;

    return {x, y};
}


vector<Point> Level::
get_chunks_near(int _x, int _y, int distance)
{
    vector<Point> chunks;

    for(int x = _x - distance; x < _x + distance; ++_x)
    for(int y = _y - distance; y < _y + distance; ++_y) {
        if(find_chunk(x, y))
            chunks.push_back({x, y});
    }

    return chunks;
}


Level::Chunk* Level::find_chunk(int x, int y)
{
    auto pos = hash_chunk_pos(x, y);

    auto itr = _data.find(pos);
    if(itr == _data.end())
        return nullptr;
    return &(itr->second);
}

Level::Chunk* Level::get_chunk(int x, int y)
{
    auto pos = hash_chunk_pos(x, y);
    return &(_data[pos]);
}


void Level::remove_chunk(int x, int y)
{
    auto pos = hash_chunk_pos(x, y);

    auto itr = _data.find(pos);
    if(itr == _data.end())
        return;

    _data.erase(itr);
}

