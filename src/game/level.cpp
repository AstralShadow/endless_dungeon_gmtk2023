#include "game/level.hpp"

using game::Level;


Level& game::level()
{
    static Level _level;
    return _level;
}


Level::Level()
{
}

Level::~Level()
{
}


Level::TileWrapper Level::at(int x, int y)
{
    return at({x, y});
}

Level::TileWrapper Level::at(Point _pos)
{
   TileWrapper wrapper;
   wrapper.parent = this;
   wrapper.pos = _pos;

   return wrapper;
}

