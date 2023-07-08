#include "game/init.hpp"
#include "game/game.hpp"
#include "game/navigation.hpp"
#include "game/hero.hpp"
#include "game/hints.hpp"
#include <iostream>

using std::cout;
using std::endl;


void game::init(int, char**, scene_uid)
{
    activate_hint(static_cast<HintKey>(next_hint++));

    generate_spawn();
    hero().move_to({0, 0});
    update_dijkstra_maps();
}


void game::deinit(scene_uid)
{

}

