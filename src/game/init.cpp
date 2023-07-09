#include "game/init.hpp"
#include "game/game.hpp"
#include "game/navigation.hpp"
#include "game/hero.hpp"
#include "game/hints.hpp"
#include "game/tick.hpp"
#include <iostream>

using std::cout;
using std::endl;


void game::init(int, char**, scene_uid)
{
#ifndef SKIP_INTRO
    activate_hint(static_cast<HintKey>(next_hint++));
#endif

    generate_spawn();
    hero().move_to({8, 8});
    update_dijkstra_maps();

#ifdef SKIP_INTRO
    for(auto i = next_hint; i <= last_intro_hint; i++) {
        auto& hint = get_hint(static_cast<HintKey>(i));
        hint.active = true;
        hint.done = true;
        hint.lifetime = 20000;
    }

    speed_mode = 2;
#endif
}


void game::deinit(scene_uid)
{

}

