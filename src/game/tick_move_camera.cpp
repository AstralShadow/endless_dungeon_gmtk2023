#include "game/tick.hpp"
#include "game/camera.hpp"
#include "config/keyboard.hpp"


using config::keyboard::keys_up;
using config::keyboard::keys_down;
using config::keyboard::keys_left;
using config::keyboard::keys_right;


void game::tick_move_camera(u32 ms)
{
    static auto* state = SDL_GetKeyboardState(nullptr);
    auto& camera = game::camera();

    auto motion = camera_speed * ms / 1000.0f;

    for(auto key : keys_up)
        if(state[key])
            camera.mid.y -= motion;

    for(auto key : keys_down)
        if(state[key])
            camera.mid.y += motion;

    for(auto key : keys_left)
        if(state[key])
            camera.mid.x -= motion;

    for(auto key : keys_right)
        if(state[key])
            camera.mid.x += motion;
}

