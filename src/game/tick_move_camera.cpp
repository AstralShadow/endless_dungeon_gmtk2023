#include "game/tick.hpp"
#include "game/camera.hpp"
#include "config/keyboard.hpp"
#include "utils/screen.hpp"
#include <SDL2/SDL_mouse.h>


using config::keyboard::keys_up;
using config::keyboard::keys_down;
using config::keyboard::keys_left;
using config::keyboard::keys_right;


const bool enable_border_to_move = false;
const int screen_border = 32;


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


    if(enable_border_to_move) {
        Point m_pos;
        SDL_GetMouseState(&m_pos.x, &m_pos.y);
        auto screen = screen_size();

        if(m_pos.x < screen_border)
            camera.mid.x -= motion;

        if(m_pos.x > screen.x - screen_border)
            camera.mid.x += motion;

        if(m_pos.y < screen_border)
            camera.mid.y -= motion;

        if(m_pos.y > screen.y - screen_border)
            camera.mid.y += motion;
    }
}

