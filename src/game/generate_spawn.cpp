#include "game/level.hpp"
#include "game/init.hpp"


void game::generate_spawn()
{
    auto level = game::level();
    const int taxicab_limit = 5;
    const int max_range = 4;


    for(int x = -max_range; x <= max_range; x++)
    for(int y = -max_range; y <= max_range; y++) {
        if(std::abs(x) + std::abs(y) < taxicab_limit)
            level.at(x, y) = ground_tile();
    }
}

