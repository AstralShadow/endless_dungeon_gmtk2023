#include "game/mouse.hpp"
#include "game/tick.hpp"
#include "utils/screen.hpp"
#include <SDL2/SDL_events.h>


bool game::in_time_control(int x, int y)
{
    auto screen = screen_size();

    int height = screen.y * 0.3 / 4;

    if(y > screen.y - 20)
        return false;
    if(y < screen.y - 20 - height)
        return false;

    float x1 = screen.x * 0.7 - 20;
    float x2 = screen.x - 20;
    float pos = (x - x1) / (x2 - x1);
    if(pos < 0 || pos > 1)
        return false;

    return true;
}

bool game::click_time_control(SDL_MouseButtonEvent& ev)
{
    auto screen = screen_size();

    int height = screen.y * 0.3 / 4;

    if(ev.y > screen.y - 20)
        return false;
    if(ev.y < screen.y - 20 - height)
        return false;

    float x1 = screen.x * 0.7 - 20;
    float x2 = screen.x - 20;
    float pos = (ev.x - x1) / (x2 - x1);
    if(pos < 0 || pos > 1)
        return false;

    if(pos < 0.25)
        speed_mode = 0;
    else if(pos < 0.5)
        speed_mode = 1;
    else if(pos < 0.75)
        speed_mode = 2;
    else
        speed_mode = 3;

    return true;
}

