#ifndef INCLUDE_GAME_NAVIGATION_HPP
#define INCLUDE_GAME_NAVIGATION_HPP

#include "utils/point.hpp"
#include <set>


namespace game
{

    /** Updates all non-wall tiles; Updates map */
    void update_dijkstra_maps();

    /** Updates tile and map at that point. */
    void update_dijkstra_maps(Point tile);

    /** Updates one tile; Returns if map needs update */
    bool update_tile_value(Point tile);

    /** Updates map starting from tile */
    void balance_dijkstra_tile(Point tile);
    void balance_dijkstra_tiles(std::set<Point> tiles);
}

#endif // INCLUDE_GAME_NAVIGATION_HPP
