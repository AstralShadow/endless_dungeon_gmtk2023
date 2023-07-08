#include "game/render.hpp"
#include "core/core.hpp"
#include "game/camera.hpp"
#include "game/tile.hpp"
#include "utils/screen.hpp"
#include <SDL2/SDL_render.h>
#include <iostream>

using std::cout;
using std::endl;

static auto& rnd = core::renderer;


void game::render_map_before(int y)
{
    auto pos = camera().fpos();
    render_map_between(pos.y - 64, y);
}

void game::render_map_after(int y)
{
    auto pos = camera().fpos();
    auto size = camera().fsize();
    render_map_between(y, pos.y + size.y + 64);
}


void game::render_map_between(int _y1, int _y2)
{
    auto c_pos = camera().fpos();
    auto c_size = camera().fsize();

    /** Only render stuff on camera */
    if(_y2 < c_pos.y - 64)
        return;
    if(_y1 < c_pos.y - 64)
        _y1 = c_pos.y - 64;

    if(_y1 > c_pos.y + c_size.y + 64)
        return;
    if(_y2 > c_pos.y + c_size.y + 64)
        _y2 = c_pos.y + c_size.y + 64;

    /** Transform into tiles coords */
    int y1 = _y1 / tile_size.y;
    int y2 = _y2 / tile_size.y;
    if(y1 == y2)
        return;


    int x1 = c_pos.x / tile_size.x - 2;
    int x2 = (c_pos.x + c_size.x) / tile_size.x + 2;

    for(int y = y1; y < y2; ++y)
    for(int x = x1; x < x2; ++x) {
        render_tile(x, y);
    }

    for(int y = y1; y < y2; ++y)
    for(int x = x1; x < x2; ++x) {
        render_tile_border(x, y);
    }
}

