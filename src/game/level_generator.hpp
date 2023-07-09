#ifndef INCLUDE_GAME_LEVEL_GENERATOR_HPP
#define INCLUDE_GAME_LEVEL_GENERATOR_HPP

#include "utils/types.hpp"
#include "utils/point.hpp"
#include <set>


namespace game
{
    extern std::set<Point> generated_chunks;

    void spawn_areas();

    void spawn_area(Point); // takes chunk coords

    /**
     * Generate different shape of area.
     * Take chunk pos
     * Return world coords
     */
    std::set<Point> plan_rect_area(Point);
    std::set<Point> plan_diamond_area(Point);

    extern bool spawning_process;
    void tick_area_generator(u32);

    Point get_spawning_area_pos();
}

#endif // INCLUDE_GAME_LEVEL_GENERATOR_HPP
