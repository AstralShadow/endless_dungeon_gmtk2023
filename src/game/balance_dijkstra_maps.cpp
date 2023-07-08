#include "game/navigation.hpp"
#include "game/level.hpp"
#include <queue>
#include <iostream>

using std::cout;
using std::endl;

using std::queue;
using std::vector;


void game::balance_dijkstra_tile(Point pos)
{
    balance_dijkstra_tiles({
        pos,
        {pos.x - 1, pos.y},
        {pos.x + 1, pos.y},
        {pos.x, pos.y - 1},
        {pos.x, pos.y + 1}
    });
}


void game::
balance_dijkstra_tiles(std::set<Point> tiles)
{
    auto& level = game::level();

    std::queue<Point> next;
    for(auto p : tiles)
        next.push(p);

    int modified_count = tiles.size();


    while(next.size() > 0) {
        auto pos = next.front();
        cout << pos.x << ":" << pos.y << endl;
        next.pop();

        Tile tile = level.at(pos);
        if(tile == default_tile())
            continue;

        vector<Point> neighbours = {
            {pos.x - 1, pos.y},
            {pos.x + 1, pos.y},
            {pos.x, pos.y - 1},
            {pos.x, pos.y + 1}
        };
        bool modified = (modified_count > 0);
        modified_count--;
        if(update_tile_value(pos)) {
            modified = true;
            tile = level.at(pos);
        }

        for(auto other_pos : neighbours) {
            Tile other = level.at(other_pos);
            if(other == default_tile())
                continue;

            if(other.interest + 5 < tile.interest) {
                tile.interest = other.interest + 5;
                modified = true;
                next.push(pos); // needs: interest_path
            }

            if(other.interest_path - 1
                 > tile.interest_path)
            {
                tile.interest_path
                    = other.interest_path - 1;
                modified = true;
            }
        }

        if(modified) {
            level.at(pos).set(tile);
            for(auto other_pos : neighbours) {
                Tile other = level.at(other_pos);
                if(other == default_tile())
                    continue;

                next.push(other_pos);
            }
        }
    }
}

