#include "game/navigation.hpp"
#include "game/level.hpp"
#include <cmath>


bool game::is_visible(Point t1, Point t2)
{
    if(t1.x == t2.x && t1.y == t2.y)
        return true;


    auto& level = game::level();

    if(t1.x == t2.x) {
        int x = t1.x;
        int y1 = std::min(t1.y, t2.y);
        int y2 = std::max(t1.y, t2.y);

        for(int y = y1; y <= y2; y++)
            if(!can_see_trough(level.at(x, y)))
                return false;

        return true;
    }

    if(t1.y == t2.y) {
        int x1 = std::min(t1.x, t2.x);
        int x2 = std::max(t1.x, t2.x);
        int y = t1.y;

        for(int x = x1; x <= x2; x++)
            if(!can_see_trough(level.at(x, y)))
                return false;

        return true;
    }

    return false;
}
