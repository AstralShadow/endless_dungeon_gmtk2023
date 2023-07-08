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
    balance_dijkstra_tiles({pos});
}


void game::
balance_dijkstra_tiles(std::set<Point> tiles)
{
    auto& level = game::level();

    std::queue<Point> next;
    for(auto p : tiles)
        next.push(p);


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
        bool modified = false;

        for(auto other_pos : neighbours) {
            Tile other = level.at(other_pos);
            if(other == default_tile())
                continue;

            if(other.interest + 10 < tile.interest)
                tile.interest = other.interest + 10;
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

