#include "game/navigation.hpp"
#include "game/level.hpp"
#include "game/hero.hpp"
#include <iostream>
#include <SDL2/SDL_timer.h>

using std::cout;
using std::endl;

static const bool verbose_log = false;


bool game::update_tile_value(Point pos)
{
    auto& level = game::level();

    Tile tile = level.at(pos);
    if(tile == default_tile())
        return false;

    bool modified = false;

    if(pos == hero().pos) {
        if(tile.hero != 0) { 
            tile.hero = 0;
            modified = true;
        }
        if(tile.hero_path > tile.hero) {
            tile.hero_path = tile.hero;
            modified = true;
        }
    } else {
        if(tile.hero != dijkstra_max) {
            tile.hero = dijkstra_max;
            modified = true;
        }
    }

    if(is_visible(pos, hero().pos)) {
        if(tile.interest > 0) {
            tile.interest = 0;
            tile.interest_path = 0;
            modified = true;
        }
    }

    if(tile.interest < dijkstra_max) {
        if(tile.interest > tile.interest_path) {
            tile.interest_path = tile.interest;
            modified = true;
        }
    }

    level.at(pos).set(tile);

    return modified;
}


bool game::tick_tile_value(Point pos, Tile tile)
{
    auto& level = game::level();

    if(tile == default_tile())
        return false;

    bool modified = false;

    if(tile.interest < dijkstra_max) {
        if(tile.interest != tile.interest_path) {
            tile.interest_path = tile.interest;
            modified = true;
        }
    }

    if(tile.hero_path < dijkstra_max) {
        if(tile.hero_path != tile.hero) {
            tile.hero_path = tile.hero;
            modified = true;
        }
    }

    level.at(pos).set(tile);

    return modified;
}


void game::tick_tile_values(u32 ms)
{
    static u32 store = 0;
    static u32 price = 100;
    store += ms;
    if(store < price)
        return;
    store -= price;

    auto& level = game::level();

    int start = SDL_GetTicks();
    std::set<Point> updated;
    for(auto& pair : level._data) {
        Point _pos = Level::unhash_chunk_pos(pair.first);

        Point c_pos = { _pos.x / 16, _pos.y / 16 };
        auto chunk = level.get_chunk(c_pos.x, c_pos.y);
        for(int i = 0; i < 256; ++i) {
            Point pos {
                _pos.x + (i % 16),
                _pos.y + (i / 16)
            };

            if(tick_tile_value(pos, chunk->tiles[i]))
                updated.insert(pos);
        }
    }

    if(verbose_log) {
        cout << "Dijkstra map tick: ";
        cout << updated.size() << " tiles" << endl;
    }

    update_dijkstra_maps(updated);
    int end = SDL_GetTicks();

    int time = end - start;
    // TODO remote the need of tile ticks.
    //cout << "Tile tick:" << time << endl;
    if(time < 5)
        price = 100;
    else if(time < 15)
        price = 200;
    else if(time < 50)
        price = 500;
    else if(time < 150)
        price = 1000;
    else
        price = 2500;
}
