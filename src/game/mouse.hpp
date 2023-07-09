#ifndef INCLUDE_GAME_MOUSE_HPP
#define INCLUDE_GAME_MOUSE_HPP

struct SDL_MouseButtonEvent;

namespace game
{

    bool in_time_control(int mouse_x, int mouse_y);
    bool click_time_control(SDL_MouseButtonEvent& ev);

    // Use when dragging. Connects diagonal paths.
    void place_tile(int x, int y);

}

#endif // INCLUDE_GAME_MOUSE_HPP
