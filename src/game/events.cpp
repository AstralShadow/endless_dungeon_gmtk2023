#include "game/game.hpp"
#include "core/core.hpp"
#include "game/hints.hpp"
#include <SDL2/SDL_events.h>


void game::keydown(SDL_KeyboardEvent& ev, scene_uid)
{
#ifndef __EMSCRIPTEN__
    auto const& scancode = ev.keysym.scancode;
    if(scancode == SDL_SCANCODE_Q)
        core::stop();
#endif


    progress_intro_hints();
}
