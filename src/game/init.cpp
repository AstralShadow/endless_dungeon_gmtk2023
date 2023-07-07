#include "game/init.hpp"
#include "game/game.hpp"

void game::init(int, char**, scene_uid)
{
    generate_spawn();
}


void game::deinit(scene_uid)
{

}

