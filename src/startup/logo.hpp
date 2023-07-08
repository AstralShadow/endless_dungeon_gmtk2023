#ifndef INCLUDE_STARTUP_LOGO_HPP
#define INCLUDE_STARTUP_LOGO_HPP

#include <SDL2/SDL_render.h>
#include "utils/point.hpp"
#include "utils/types.hpp"
#include <string>

namespace startup
{
    SDL_Texture* gmtk_logo();
    Point gmtk_logo_size();

    extern SDL_Rect gmtk_logo_pos;
    extern u32 time;

    const u32 text_enter_start = 250;
    const u32 text_enter_end = 1500;

    const u32 enter_start = 1500;
    const u32 enter_end = 2750;

    const u32 text_exit_start = 4750;
    const u32 text_exit_end = 6000;

    const u32 exit_start = 4250;
    const u32 exit_end = 5500;

    const u32 next_scene_t = 6500;
    const std::string next_scene = "game";
}

#endif // INCLUDE_STARTUP_LOGO_HPP
