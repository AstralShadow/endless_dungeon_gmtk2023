#ifndef INCLUDE_CONFIG_KEYBOARD_HPP
#define INCLUDE_CONFIG_KEYBOARD_HPP

#include "utils/types.hpp"
#include <SDL2/SDL_keyboard.h>

#ifdef USE_ESDF
    #undef USE_ESDF
    #define USE_ESDF 1
#else
    #define USE_ESDF 0
#endif

namespace config::keyboard
{
    const u8 keys_up[] {
        USE_ESDF ? SDL_SCANCODE_E : SDL_SCANCODE_W,
        SDL_SCANCODE_UP
    };
    const u8 keys_left[] {
        USE_ESDF ? SDL_SCANCODE_S : SDL_SCANCODE_A,
        SDL_SCANCODE_LEFT
    };
    const u8 keys_down[] {
        USE_ESDF ? SDL_SCANCODE_D : SDL_SCANCODE_S,
        SDL_SCANCODE_DOWN
    };
    const u8 keys_right[] {
        USE_ESDF ? SDL_SCANCODE_F : SDL_SCANCODE_D,
        SDL_SCANCODE_RIGHT
    };
}

#endif // INCLUDE_CONFIG_KEYBOARD_HPP
