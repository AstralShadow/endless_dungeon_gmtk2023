#include "game/init.hpp"
#include "game/game.hpp"
#include "game/navigation.hpp"
#include "game/hero.hpp"
#include <iostream>

using std::cout;
using std::endl;


void game::init(int, char**, scene_uid)
{
    generate_spawn();

    update_dijkstra_maps();

    hero().move_to({0, 0});
}


void game::deinit(scene_uid)
{

}

