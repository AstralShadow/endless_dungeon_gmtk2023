#include "game/game.hpp"
#include "core/core.hpp"
#include "game/hints.hpp"
#include "config/keyboard.hpp"
#include <SDL2/SDL_events.h>

using config::keyboard::keys_up;
using config::keyboard::keys_down;
using config::keyboard::keys_left;
using config::keyboard::keys_right;


void game::keydown(SDL_KeyboardEvent& ev, scene_uid)
{
    auto const& scancode = ev.keysym.scancode;

#ifndef __EMSCRIPTEN__
    if(scancode == SDL_SCANCODE_Q)
        core::stop();
#endif // __EMSCRIPTEN__


    const u8 camera_keys[] = {
        USE_ESDF ? SDL_SCANCODE_E : SDL_SCANCODE_W,
        SDL_SCANCODE_UP,
        USE_ESDF ? SDL_SCANCODE_S : SDL_SCANCODE_A,
        SDL_SCANCODE_LEFT,
        USE_ESDF ? SDL_SCANCODE_D : SDL_SCANCODE_S,
        SDL_SCANCODE_DOWN,
        USE_ESDF ? SDL_SCANCODE_F : SDL_SCANCODE_D,
        SDL_SCANCODE_RIGHT
    };

    bool moving_camera = false;
    for(auto key : camera_keys)
        if(scancode == key)
            moving_camera = true;

    if(!moving_camera)
        progress_intro_hints();
}
