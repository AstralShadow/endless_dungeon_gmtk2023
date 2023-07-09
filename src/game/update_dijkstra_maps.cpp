#include "game/navigation.hpp"
#include "game/level.hpp"
#include <set>
#include <iostream>

using std::cout;
using std::endl;

const bool verbose_log = false;


void game::update_dijkstra_maps()
{
    cout << "Updating Dijkstra maps..." << endl;

    std::set<Point> updated;
    for(auto& pair : level()._data) {
        Point _pos = Level::unhash_chunk_pos(pair.first);

        for(int i = 0; i < 256; ++i) {
            Point pos {
                _pos.x + (i % 16),
                _pos.y + (i / 16)
            };

            if(update_tile_value(pos))
                updated.insert(pos);
        }
    }

    cout << "Dijkstra map update: ";
    cout << updated.size() << " tiles" << endl;

    balance_dijkstra_tiles(updated);
}

void game::update_dijkstra_maps(Point tile)
{
    if(verbose_log) {
        cout << "Updating Dijkstra map at ";
        cout << tile.x << ":" << tile.y << endl;
    }

    update_tile_value(tile);

    balance_dijkstra_tile(tile);
}


void game::update_dijkstra_maps(std::set<Point> tiles)
{
    for(auto tile : tiles)
        update_tile_value(tile);

    for(auto tile : tiles)
        balance_dijkstra_tile(tile);
}

