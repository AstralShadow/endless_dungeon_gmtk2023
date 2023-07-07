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

