#include "game/level.hpp"
#include "game/init.hpp"
#include "game/hero.hpp"
#include "game/navigation.hpp"
#include <iostream>

using std::cout;
using std::endl;


void game::generate_spawn()
{
    auto& level = game::level();
    const int taxicab_limit = 5;
    const int max_range = 3;

    for(int x = -max_range; x <= max_range; x++)
    for(int y = -max_range; y <= max_range; y++) {
        if(std::abs(x) + std::abs(y) < taxicab_limit) {
            level.at(x + 8, y + 8).set(ground_tile());
        }
    }

    cout << "Created spawn area" << endl;
}

