#include "game/navigation.hpp"
#include "game/level.hpp"
#include "game/hero.hpp"
#include <iostream>

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


bool game::tick_tile_value(Point pos)
{
    auto& level = game::level();

    Tile tile = level.at(pos);
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
    store += ms;
    if(store < 100)
        return;
    store -= 100;


    std::set<Point> updated;
    for(auto& pair : level()._data) {
        Point _pos = Level::unhash_chunk_pos(pair.first);

        for(int i = 0; i < 256; ++i) {
            Point pos {
                _pos.x + (i % 16),
                _pos.y + (i / 16)
            };

            if(tick_tile_value(pos))
                updated.insert(pos);
        }
    }

    if(verbose_log) {
        cout << "Dijkstra map tick: ";
        cout << updated.size() << " tiles" << endl;
    }

    update_dijkstra_maps(updated);
}
