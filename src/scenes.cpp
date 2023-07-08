#include "core/scene.hpp"

#include "game/game.hpp"
#include "startup/startup.hpp"


void core::register_scenes()
{
    core::scene<game::scene_uid>("game");
    core::scene<startup::scene_uid>("startup");

#ifndef SKIP_INTRO
    core::set_scene("startup");
#else // SKIP_INTRO
    core::set_scene("game");
#endif // SKIP_INTRO
}


