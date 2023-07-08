#include "game/game.hpp"
#include "game/camera.hpp"
#include "utils/screen.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>


void game::
mouse_motion(SDL_MouseMotionEvent& ev, scene_uid)
{
    if(ev.state & SDL_BUTTON_MMASK) {
        // Dragging camera

        auto& camera = game::camera();
        camera.mid.x -= ev.xrel / camera.zoom;
        camera.mid.y -= ev.yrel / camera.zoom;
    }
}


void game::
mouse_wheel(SDL_MouseWheelEvent& ev, scene_uid)
{
    auto& camera = game::camera();
    auto screen = screen_size();

    Point m_pos;
    SDL_GetMouseState(&m_pos.x, &m_pos.y);

    auto old_zoom = camera.zoom;
    camera.zoom += ev.y * 0.15f;

    if(camera.zoom < 0.5)
        camera.zoom = 0.5;

    if(camera.zoom > 2.5)
        camera.zoom = 2.5;
}

