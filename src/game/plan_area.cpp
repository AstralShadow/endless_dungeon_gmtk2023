#include "level_generator.hpp"
#include "utils/trandom.hpp"

namespace game
{
    struct RNG_Token;
}


std::set<Point> game::plan_rect_area(Point chunk)
{
    Point top {
        chunk.x * 16 + random<0, 6, RNG_Token>(),
        chunk.y * 16 + random<0, 6, RNG_Token>()
    };
    Point size {
        random<6, 12, RNG_Token>(),
        random<6, 12, RNG_Token>()
    };

    std::set<Point> points;

    for(int x = top.x; x < top.x + size.x; ++x)
    for(int y = top.y; y < top.y + size.y; ++y) {
        if(random<0, 20, RNG_Token>() != 4)
            points.insert({x, y});
    }

    return points;
}

std::set<Point> game::plan_diamond_area(Point chunk)
{
    Point mid {
        chunk.x * 16 + random<6, 10, RNG_Token>(),
        chunk.y * 16 + random<6, 10, RNG_Token>()
    };

    int size = random<3, 5, RNG_Token>();
    int taxicab_r = size + random<1, 3, RNG_Token>();

    std::set<Point> points;

    for(int x = mid.x - size; x <= mid.x + size; ++x)
    for(int y = mid.y - size; y <= mid.y + size; ++y) {
        int dx = std::abs(x - mid.x);
        int dy = std::abs(y - mid.y);
        if(dx + dy > taxicab_r)
            continue;

        if(random<0, 20, RNG_Token>() != 4)
            points.insert({x, y});
    }

    return points;
}


