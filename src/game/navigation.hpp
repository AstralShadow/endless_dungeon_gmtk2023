#ifndef INCLUDE_GAME_NAVIGATION_HPP
#define INCLUDE_GAME_NAVIGATION_HPP

#include "utils/types.hpp"
#include "utils/point.hpp"
#include <set>


namespace game
{

    /** Updates all non-wall tiles; Updates map */
    void update_dijkstra_maps();

    /** Updates tile and map at that point. */
    void update_dijkstra_maps(Point tile);
    void update_dijkstra_maps(std::set<Point> tiles);

    /** Updates one tile; Returns if map needs update */
    bool update_tile_value(Point tile);

    /** Updates map starting from tile */
    void balance_dijkstra_tile(Point tile);
    void balance_dijkstra_tiles(std::set<Point> tiles);


    bool is_visible(Point t1, Point t2);

    /** Controls Dijkstra map value decaying */
    bool tick_tile_value(Point tile);
    void tick_tile_values(u32 ms);
}

#endif // INCLUDE_GAME_NAVIGATION_HPP
